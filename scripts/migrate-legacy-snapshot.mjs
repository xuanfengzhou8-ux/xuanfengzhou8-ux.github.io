import { mkdir, readFile, readdir, writeFile } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { parse, stringify } from "yaml";

const repoRoot = fileURLToPath(new URL("..", import.meta.url));
const contentRoot = path.join(repoRoot, "content");
const snapshotPath = path.join(repoRoot, "data", "public-data.json");

const directoryByCourse = new Map([
  ["LVGL图形框架", "LVGL_content-notes"],
  ["Qt应用编程", "Qt_content-notes"],
  ["STM32开发基础", "STM32_content-notes"],
  ["FreeRTOS嵌入式操作系统", "FreeRTOS_content-notes"],
  ["嵌入式AI基础", "EmbeddedAI_content-notes"],
  ["AI辅助嵌入式开发", "AIAssistedDev_content-notes"],
]);

const snapshot = JSON.parse(await readFile(snapshotPath, "utf8"));
const entries = await readdir(contentRoot, { withFileTypes: true });
const managedTitles = new Set();

for (const entry of entries) {
  if (!entry.isDirectory()) continue;
  try {
    const manifest = parse(
      await readFile(path.join(contentRoot, entry.name, "import-manifest.yml"), "utf8"),
    );
    if (manifest?.target?.course?.title) managedTitles.add(manifest.target.course.title);
  } catch (error) {
    if (error?.code !== "ENOENT") throw error;
  }
}

const safeName = (value) =>
  value.replace(/[<>:"/\\|?*]/g, "-").replace(/[. ]+$/g, "").trim();
const sameId = (left, right) => String(left) === String(right);
let migratedCourses = 0;
let migratedArticles = 0;

for (const course of snapshot.courses) {
  if (managedTitles.has(course.title)) continue;
  const directory = directoryByCourse.get(course.title);
  if (!directory) {
    throw new Error(`No migration directory mapping for course: ${course.title}`);
  }

  const courseRoot = path.join(contentRoot, directory);
  const notesRoot = path.join(courseRoot, "笔记");
  await mkdir(notesRoot, { recursive: true });

  const learningPath = snapshot.paths.find((item) => sameId(item.id, course.pathId));
  if (!learningPath) throw new Error(`Missing learning path for course: ${course.title}`);

  const chapters = snapshot.chapters
    .filter((item) => sameId(item.courseId, course.id))
    .sort((a, b) => Number(a.sortOrder) - Number(b.sortOrder));
  const content = [];

  for (const chapter of chapters) {
    const summaries = snapshot.articleSummaries
      .filter((item) => sameId(item.chapterId, chapter.id))
      .sort((a, b) => Number(a.sortOrder) - Number(b.sortOrder));
    for (const summary of summaries) {
      const detail = snapshot.articleDetails.find((item) => sameId(item.article.id, summary.id));
      if (!detail) throw new Error(`Missing article detail: ${summary.title}`);
      const order = content.length + 1;
      const file = `笔记/${String(order).padStart(2, "0")}-${safeName(chapter.title)}.md`;
      const markdown = String(detail.article.contentMd ?? "").trimEnd();
      if (!markdown.startsWith("# ")) {
        throw new Error(`Legacy article must start with one H1: ${summary.title}`);
      }
      await writeFile(path.join(courseRoot, file), `${markdown}\n`, "utf8");
      content.push({
        sourceKey: `legacy:${course.id}:article:${summary.id}`,
        file,
        chapterTitle: chapter.title,
        articleSlug: summary.slug,
        summary: summary.summary ?? "",
        keywords: String(summary.keywords ?? "")
          .split(",")
          .map((item) => item.trim())
          .filter(Boolean),
        sortOrder: order,
      });
      migratedArticles += 1;
    }
  }

  const manifest = {
    schemaVersion: 1,
    packageId: `legacy-course-${course.id}`,
    version: "1.0.0",
    title: `${course.title}课程内容包`,
    encoding: "UTF-8",
    target: {
      learningPath: {
        sourceKey: `path:${learningPath.slug}`,
        slug: learningPath.slug,
        name: learningPath.name,
        description: learningPath.description ?? "",
        sortOrder: learningPath.sortOrder,
      },
      course: {
        sourceKey: `course:legacy:${course.id}`,
        title: course.title,
        description: course.description ?? "",
        level: course.level,
        sortOrder: course.sortOrder,
        archiveUnmanagedContent: true,
      },
    },
    defaults: {
      status: 1,
      keywords: [course.title],
      includeReferencedAssets: true,
    },
    content,
  };

  await writeFile(
    path.join(courseRoot, "import-manifest.yml"),
    stringify(manifest, { lineWidth: 0 }),
    "utf8",
  );
  migratedCourses += 1;
}

console.log(`Migrated ${migratedCourses} legacy courses and ${migratedArticles} articles.`);
