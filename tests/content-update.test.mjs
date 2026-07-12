import assert from "node:assert/strict";
import { execFile } from "node:child_process";
import { cp, mkdtemp, mkdir, readFile, rm, writeFile } from "node:fs/promises";
import os from "node:os";
import path from "node:path";
import { promisify } from "node:util";
import { fileURLToPath } from "node:url";
import test from "node:test";
import { parse, stringify } from "yaml";

const run = promisify(execFile);
const repoRoot = fileURLToPath(new URL("..", import.meta.url));

test("a new manifest chapter is automatically included in generated website data", async () => {
  const temporaryRoot = await mkdtemp(path.join(os.tmpdir(), "embedded-content-"));
  const contentRoot = path.join(temporaryRoot, "content");
  const dataRoot = path.join(temporaryRoot, "data");
  try {
    await cp(path.join(repoRoot, "content"), contentRoot, { recursive: true });
    await mkdir(dataRoot, { recursive: true });

    const courseRoot = path.join(contentRoot, "LinuxNetwork_content-notes");
    const manifestFile = path.join(courseRoot, "import-manifest.yml");
    const manifest = parse(await readFile(manifestFile, "utf8"));
    manifest.content.push({
      sourceKey: "acceptance:linux-net:chapter:06",
      file: "笔记/06-自动更新验收.md",
      chapterTitle: "自动更新验收",
      articleSlug: "acceptance-auto-content-update",
      sortOrder: 6,
    });
    await writeFile(manifestFile, stringify(manifest, { lineWidth: 0 }), "utf8");
    await writeFile(
      path.join(courseRoot, "笔记", "06-自动更新验收.md"),
      "# 自动更新验收\n\n这是一篇仅在临时测试目录中生成的验收文章。\n",
      "utf8",
    );

    await run(process.execPath, [path.join(repoRoot, "scripts", "build-content-data.mjs")], {
      env: { ...process.env, CONTENT_ROOT: contentRoot, DATA_ROOT: dataRoot },
    });
    const snapshot = JSON.parse(await readFile(path.join(dataRoot, "public-data.json"), "utf8"));
    assert.equal(snapshot.articleDetails.length, 64);
    assert.ok(
      snapshot.articleDetails.some(
        (item) => item.article.slug === "acceptance-auto-content-update",
      ),
    );
  } finally {
    await rm(temporaryRoot, { recursive: true, force: true });
  }
});
