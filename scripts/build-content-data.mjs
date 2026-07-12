import { createHash } from "node:crypto";
import { access, mkdir, readFile, readdir, writeFile } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { parse } from "yaml";

const repoRoot = fileURLToPath(new URL("..", import.meta.url));
const contentRoot = path.resolve(process.env.CONTENT_ROOT ?? path.join(repoRoot, "content"));
const dataRoot = path.resolve(process.env.DATA_ROOT ?? path.join(repoRoot, "data"));
const snapshotPath = path.join(dataRoot, "public-data.json");
const catalogPath = path.join(dataRoot, "catalog.json");
const searchPath = path.join(dataRoot, "search-index.json");

const sha256 = (value) => createHash("sha256").update(value).digest("hex");
const stableId = (kind, sourceKey) => `${kind}-${sha256(sourceKey).slice(0, 12)}`;
const sameId = (left, right) => String(left) === String(right);
const bySortOrder = (left, right) => Number(left.sortOrder ?? 0) - Number(right.sortOrder ?? 0);
const unique = (values) => [...new Set(values.filter(Boolean))];

async function readJsonIfPresent(file) {
  try {
    return JSON.parse(await readFile(file, "utf8"));
  } catch (error) {
    if (error?.code === "ENOENT") return null;
    throw error;
  }
}

function resolveContentFile(root, relativeFile) {
  const resolvedRoot = path.resolve(root);
  const resolvedFile = path.resolve(root, relativeFile);
  if (resolvedFile === resolvedRoot || !resolvedFile.startsWith(`${resolvedRoot}${path.sep}`)) {
    throw new Error(`Unsafe content path: ${relativeFile}`);
  }
  return resolvedFile;
}

function validateMarkdown(markdown, relativeFile) {
  let fenced = false;
  let marker = "";
  let h1Count = 0;
  for (const line of markdown.split(/\r?\n/)) {
    const stripped = line.trimStart();
    if (stripped.startsWith("```") || stripped.startsWith("~~~")) {
      const current = stripped.slice(0, 3);
      if (!fenced) {
        fenced = true;
        marker = current;
      } else if (current === marker) {
        fenced = false;
        marker = "";
      }
    } else if (!fenced && line.startsWith("# ")) {
      h1Count += 1;
    }
  }
  if (fenced) throw new Error(`Unclosed code fence: ${relativeFile}`);
  if (h1Count !== 1) {
    throw new Error(`Expected exactly one H1 in ${relativeFile}; found ${h1Count}`);
  }
}

function deriveSummary(markdown) {
  let fenced = false;
  for (const original of markdown.split(/\r?\n/)) {
    const trimmed = original.trim();
    if (trimmed.startsWith("```") || trimmed.startsWith("~~~")) {
      fenced = !fenced;
      continue;
    }
    if (
      fenced ||
      !trimmed ||
      trimmed.startsWith("#") ||
      trimmed.startsWith("|") ||
      /^[-*+]\s/.test(trimmed)
    ) continue;
    return trimmed.replace(/^>\s*/, "").replace(/[`*_]/g, "").slice(0, 220);
  }
  return "";
}

function sourceLifecycle(previous, sourceKey, sourceHash, generatedAt) {
  return {
    id: previous?.id ?? stableId("item", sourceKey),
    sourceKey,
    sourceHash,
    createdAt: previous?.createdAt ?? generatedAt,
    updatedAt:
      previous && (!previous.sourceHash || previous.sourceHash === sourceHash)
        ? previous.updatedAt
        : generatedAt,
    isDeleted: 0,
  };
}

function assertUnique(records, field, label) {
  const seen = new Set();
  for (const record of records) {
    const value = String(record[field]);
    if (seen.has(value)) throw new Error(`Duplicate ${label} ${field}: ${value}`);
    seen.add(value);
  }
}

const previous = (await readJsonIfPresent(snapshotPath)) ?? {
  paths: [], courses: [], chapters: [], articleSummaries: [], articleDetails: [], projects: [],
};
const previousArticles = previous.articleDetails.map((item) => item.article);
const now = new Date().toISOString();
const sourceParts = [];
const paths = [];
const courses = [];
const chapters = [];
const articleSummaries = [];
const articleDetails = [];
const pathBySourceKey = new Map();
const courseBySourceKey = new Map();

const entries = (await readdir(contentRoot, { withFileTypes: true }))
  .filter((entry) => entry.isDirectory())
  .sort((a, b) => a.name.localeCompare(b.name, "zh-CN"));

for (const entry of entries) {
  const courseRoot = path.join(contentRoot, entry.name);
  const manifestFile = path.join(courseRoot, "import-manifest.yml");
  try {
    await access(manifestFile);
  } catch {
    continue;
  }

  const manifestText = await readFile(manifestFile, "utf8");
  sourceParts.push(`${entry.name}/import-manifest.yml\0${manifestText}`);
  const manifest = parse(manifestText);
  const learningPath = manifest?.target?.learningPath;
  const courseConfig = manifest?.target?.course;
  const items = manifest?.content;
  if (!learningPath?.sourceKey || !learningPath?.slug || !learningPath?.name) {
    throw new Error(`Invalid learning path in ${entry.name}/import-manifest.yml`);
  }
  if (!courseConfig?.sourceKey || !courseConfig?.title || !Array.isArray(items)) {
    throw new Error(`Invalid course in ${entry.name}/import-manifest.yml`);
  }

  let pathRecord = pathBySourceKey.get(learningPath.sourceKey);
  if (!pathRecord) {
    const oldPath = previous.paths.find(
      (item) => item.sourceKey === learningPath.sourceKey || item.slug === learningPath.slug,
    );
    const metadata = JSON.stringify(learningPath);
    pathRecord = {
      ...sourceLifecycle(oldPath, learningPath.sourceKey, sha256(metadata), now),
      id: oldPath?.id ?? stableId("path", learningPath.sourceKey),
      name: learningPath.name,
      slug: learningPath.slug,
      description: learningPath.description ?? oldPath?.description ?? "",
      icon: learningPath.icon ?? oldPath?.icon ?? null,
      sortOrder: Number(learningPath.sortOrder ?? oldPath?.sortOrder ?? paths.length + 1),
      status: Number(learningPath.status ?? oldPath?.status ?? 1),
    };
    pathBySourceKey.set(learningPath.sourceKey, pathRecord);
    paths.push(pathRecord);
  } else if (pathRecord.slug !== learningPath.slug || pathRecord.name !== learningPath.name) {
    throw new Error(`Conflicting learning path definition: ${learningPath.sourceKey}`);
  }

  if (courseBySourceKey.has(courseConfig.sourceKey)) {
    throw new Error(`Duplicate course sourceKey: ${courseConfig.sourceKey}`);
  }
  const oldCourse = previous.courses.find(
    (item) => item.sourceKey === courseConfig.sourceKey || item.title === courseConfig.title,
  );
  const courseHash = sha256(JSON.stringify(courseConfig));
  const courseRecord = {
    ...sourceLifecycle(oldCourse, courseConfig.sourceKey, courseHash, now),
    id: oldCourse?.id ?? stableId("course", courseConfig.sourceKey),
    pathId: pathRecord.id,
    title: courseConfig.title,
    description: courseConfig.description ?? "",
    coverUrl: courseConfig.coverUrl ?? oldCourse?.coverUrl ?? null,
    level: courseConfig.level ?? "BEGINNER",
    sortOrder: Number(courseConfig.sortOrder ?? 0),
    status: Number(courseConfig.status ?? manifest.defaults?.status ?? 1),
  };
  courseBySourceKey.set(courseConfig.sourceKey, courseRecord);
  courses.push(courseRecord);

  const itemKeys = new Set();
  const itemSlugs = new Set();
  const itemOrders = new Set();
  for (const item of items) {
    if (!item?.sourceKey || !item?.file || !item?.chapterTitle || !item?.articleSlug) {
      throw new Error(`Invalid content entry in ${entry.name}/import-manifest.yml`);
    }
    for (const [set, value, label] of [
      [itemKeys, item.sourceKey, "sourceKey"],
      [itemSlugs, item.articleSlug, "articleSlug"],
      [itemOrders, String(item.sortOrder), "sortOrder"],
    ]) {
      if (set.has(value)) throw new Error(`Duplicate ${label} in ${entry.name}: ${value}`);
      set.add(value);
    }

    const markdownFile = resolveContentFile(courseRoot, item.file);
    const markdown = await readFile(markdownFile, "utf8");
    validateMarkdown(markdown, `${entry.name}/${item.file}`);
    sourceParts.push(`${entry.name}/${item.file}\0${markdown}`);
    const itemHash = sha256(`${JSON.stringify(item)}\0${markdown}`);
    const oldChapter = previous.chapters.find(
      (candidate) =>
        candidate.sourceKey === item.sourceKey ||
        (candidate.title === item.chapterTitle && sameId(candidate.courseId, oldCourse?.id)),
    );
    const oldArticle = previousArticles.find(
      (candidate) => candidate.sourceKey === item.sourceKey || candidate.slug === item.articleSlug,
    );
    const chapterRecord = {
      ...sourceLifecycle(oldChapter, item.sourceKey, itemHash, now),
      id: oldChapter?.id ?? stableId("chapter", item.sourceKey),
      courseId: courseRecord.id,
      title: item.chapterTitle,
      description: item.chapterDescription ?? oldChapter?.description ?? "",
      sortOrder: Number(item.sortOrder ?? 0),
      status: Number(item.status ?? manifest.defaults?.status ?? 1),
    };
    const keywords = unique([
      ...(Array.isArray(manifest.defaults?.keywords) ? manifest.defaults.keywords : []),
      ...(Array.isArray(item.keywords) ? item.keywords : []),
    ]).join(",");
    const articleRecord = {
      ...sourceLifecycle(oldArticle, item.sourceKey, itemHash, now),
      id: oldArticle?.id ?? stableId("article", item.sourceKey),
      chapterId: chapterRecord.id,
      title: item.articleTitle ?? item.chapterTitle,
      slug: item.articleSlug,
      summary: item.summary ?? oldArticle?.summary ?? deriveSummary(markdown),
      contentMd: markdown.trimEnd(),
      keywords: keywords || oldArticle?.keywords || item.chapterTitle,
      sortOrder: Number(item.articleSortOrder ?? 1),
      status: Number(item.status ?? manifest.defaults?.status ?? 1),
    };
    chapters.push(chapterRecord);
    articleSummaries.push(articleRecord);
    articleDetails.push({
      article: articleRecord,
      chapterId: chapterRecord.id,
      chapterTitle: chapterRecord.title,
      courseId: courseRecord.id,
      courseTitle: courseRecord.title,
      pathId: pathRecord.id,
      pathName: pathRecord.name,
    });
  }
}

const projects = [];
const projectRoot = path.join(contentRoot, "Project_content-notes");
const projectManifestFile = path.join(projectRoot, "projects.json");
const projectManifestText = await readFile(projectManifestFile, "utf8");
sourceParts.push(`Project_content-notes/projects.json\0${projectManifestText}`);
const projectManifest = JSON.parse(projectManifestText);
for (const project of projectManifest.projects ?? []) {
  if (!project.title || !project.file) throw new Error("Invalid project content entry");
  const markdownFile = resolveContentFile(projectRoot, project.file);
  const markdown = await readFile(markdownFile, "utf8");
  validateMarkdown(markdown, `Project_content-notes/${project.file}`);
  sourceParts.push(`Project_content-notes/${project.file}\0${markdown}`);
  const sourceKey = project.sourceKey ?? `project:${sha256(project.title).slice(0, 16)}`;
  const sourceHash = sha256(`${JSON.stringify(project)}\0${markdown}`);
  const oldProject = previous.projects.find(
    (item) => item.sourceKey === sourceKey || item.title === project.title,
  );
  projects.push({
    ...sourceLifecycle(oldProject, sourceKey, sourceHash, now),
    id: oldProject?.id ?? stableId("project", sourceKey),
    title: project.title,
    summary: project.summary ?? oldProject?.summary ?? deriveSummary(markdown),
    contentMd: markdown.trimEnd(),
    coverUrl: project.coverUrl ?? oldProject?.coverUrl ?? null,
    difficulty: project.difficulty ?? "BEGINNER",
    knowledgePoints: project.knowledgePoints ?? "",
    sortOrder: Number(project.sortOrder ?? 0),
    status: Number(project.status ?? 1),
  });
}

paths.sort(bySortOrder);
courses.sort((a, b) => sameId(a.pathId, b.pathId) ? bySortOrder(a, b) : 0);
chapters.sort(bySortOrder);
articleSummaries.sort(bySortOrder);
projects.sort(bySortOrder);

assertUnique(paths, "id", "path");
assertUnique(courses, "id", "course");
assertUnique(chapters, "id", "chapter");
assertUnique(articleSummaries, "id", "article");
assertUnique(articleSummaries, "slug", "article");
assertUnique(projects, "id", "project");

const contentHash = sha256(sourceParts.sort().join("\n"));
const generatedAt = previous.contentHash === contentHash ? previous.generatedAt : now;
const snapshot = {
  generatedAt,
  contentHash,
  paths,
  courses,
  chapters,
  articleSummaries,
  articleDetails,
  projects,
};
const catalog = { generatedAt, contentHash, paths, courses };
const searchIndex = {
  generatedAt,
  contentHash,
  courses,
  projects,
  articles: articleDetails.map((item) => ({
    id: item.article.id,
    title: item.article.title,
    summary: item.article.summary,
    keywords: item.article.keywords,
    courseTitle: item.courseTitle,
    chapterTitle: item.chapterTitle,
  })),
};

await mkdir(dataRoot, { recursive: true });
await writeFile(snapshotPath, `${JSON.stringify(snapshot)}\n`, "utf8");
await writeFile(catalogPath, `${JSON.stringify(catalog)}\n`, "utf8");
await writeFile(searchPath, `${JSON.stringify(searchIndex)}\n`, "utf8");
console.log(
  `Generated ${paths.length} paths, ${courses.length} courses, ${chapters.length} chapters, ${articleDetails.length} articles, and ${projects.length} projects.`,
);
