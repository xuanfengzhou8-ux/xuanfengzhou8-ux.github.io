import { mkdir, writeFile } from "node:fs/promises";
import { dirname } from "node:path";
import { fileURLToPath } from "node:url";

const apiBase = process.env.KB_API_BASE ?? "http://localhost:8080/api";
const username = process.env.KB_EXPORT_USERNAME ?? "student";
const password = process.env.KB_EXPORT_PASSWORD ?? "password";

async function request(path, options = {}) {
  const response = await fetch(`${apiBase}${path}`, options);
  const body = await response.json();
  if (!response.ok || body.code !== 0) {
    throw new Error(body.message || `Request failed: ${path}`);
  }
  return body.data;
}

const login = await request("/auth/login", {
  method: "POST",
  headers: { "content-type": "application/json" },
  body: JSON.stringify({ username, password }),
});
const headers = { authorization: `Bearer ${login.token}` };
const get = (path) => request(path, { headers });

const [paths, courses, projects] = await Promise.all([
  get("/paths"),
  get("/courses"),
  get("/projects"),
]);

const chapterGroups = await Promise.all(
  courses.map((course) => get(`/courses/${course.id}/chapters`)),
);
const chapters = chapterGroups.flat();
const articleGroups = await Promise.all(
  chapters.map((chapter) => get(`/chapters/${chapter.id}/articles`)),
);
const articleSummaries = articleGroups.flat();
const articleDetails = await Promise.all(
  articleSummaries.map((article) => get(`/articles/${article.id}`)),
);
const projectDetails = await Promise.all(
  projects.map((project) => get(`/projects/${project.id}`)),
);

const snapshot = {
  generatedAt: new Date().toISOString(),
  paths,
  courses,
  chapters,
  articleSummaries,
  articleDetails,
  projects: projectDetails,
};

const output = fileURLToPath(new URL("../data/public-data.json", import.meta.url));
await mkdir(dirname(output), { recursive: true });
await writeFile(output, `${JSON.stringify(snapshot)}\n`, "utf8");

const catalogOutput = fileURLToPath(new URL("../data/catalog.json", import.meta.url));
await writeFile(catalogOutput, `${JSON.stringify({ paths, courses })}\n`, "utf8");

const searchOutput = fileURLToPath(new URL("../data/search-index.json", import.meta.url));
await writeFile(searchOutput, `${JSON.stringify({
  courses,
  projects: projectDetails,
  articles: articleDetails.map((item) => ({
    id: item.article.id,
    title: item.article.title,
    summary: item.article.summary,
    keywords: item.article.keywords,
    courseTitle: item.courseTitle,
    chapterTitle: item.chapterTitle,
  })),
})}\n`, "utf8");
console.log(
  `Exported ${paths.length} paths, ${courses.length} courses, ${chapters.length} chapters, ${articleDetails.length} articles, and ${projects.length} projects.`,
);
