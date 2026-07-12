import assert from "node:assert/strict";
import { readFile } from "node:fs/promises";
import test from "node:test";

async function render(pathname = "/") {
  const workerUrl = new URL("../dist/server/index.js", import.meta.url);
  workerUrl.searchParams.set("test", `${process.pid}-${Date.now()}-${pathname}`);
  const { default: worker } = await import(workerUrl.href);
  return worker.fetch(
    new Request(`http://localhost${pathname}`, {
      headers: { accept: "text/html" },
    }),
    {
      ASSETS: {
        fetch: async () => new Response("Not found", { status: 404 }),
      },
    },
    {
      waitUntil() {},
      passThroughOnException() {},
    },
  );
}

test("server-renders the embedded knowledge base home page", async () => {
  const response = await render();
  assert.equal(response.status, 200);
  assert.match(response.headers.get("content-type") ?? "", /^text\/html\b/i);

  const html = await response.text();
  assert.match(html, /<html lang="zh-CN">/i);
  assert.match(html, /<title>嵌入式知识库<\/title>/i);
  assert.match(html, /把零散知识/);
  assert.match(html, /<dt>5<\/dt><dd>学习路径<\/dd>/);
  assert.match(html, /<dt>14<\/dt><dd>门课程<\/dd>/);
  assert.match(html, /<dt>63<\/dt><dd>篇文章<\/dd>/);
  assert.match(html, /<dt>3<\/dt><dd>个项目<\/dd>/);
  assert.match(html, /C语言基础/);
  assert.match(html, /搜索知识库/);
});

test("generated content keeps every route and relationship valid", async () => {
  const snapshot = JSON.parse(
    await readFile(new URL("../data/public-data.json", import.meta.url), "utf8"),
  );
  assert.equal(snapshot.paths.length, 5);
  assert.equal(snapshot.courses.length, 14);
  assert.equal(snapshot.chapters.length, 63);
  assert.equal(snapshot.articleSummaries.length, 63);
  assert.equal(snapshot.articleDetails.length, 63);
  assert.equal(snapshot.projects.length, 3);

  const pathIds = new Set(snapshot.paths.map((item) => String(item.id)));
  const courseIds = new Set(snapshot.courses.map((item) => String(item.id)));
  const chapterIds = new Set(snapshot.chapters.map((item) => String(item.id)));
  const articleIds = new Set(snapshot.articleSummaries.map((item) => String(item.id)));
  assert.equal(pathIds.size, snapshot.paths.length);
  assert.equal(courseIds.size, snapshot.courses.length);
  assert.equal(chapterIds.size, snapshot.chapters.length);
  assert.equal(articleIds.size, snapshot.articleSummaries.length);

  for (const course of snapshot.courses) assert.ok(pathIds.has(String(course.pathId)));
  for (const chapter of snapshot.chapters) assert.ok(courseIds.has(String(chapter.courseId)));
  for (const article of snapshot.articleSummaries) assert.ok(chapterIds.has(String(article.chapterId)));
  for (const detail of snapshot.articleDetails) {
    assert.ok(articleIds.has(String(detail.article.id)));
    assert.ok(chapterIds.has(String(detail.chapterId)));
    assert.ok(courseIds.has(String(detail.courseId)));
    assert.ok(pathIds.has(String(detail.pathId)));
  }
});
