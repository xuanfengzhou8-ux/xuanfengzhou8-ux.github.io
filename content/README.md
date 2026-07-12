# 学习内容仓库

`content/` 是课程、章节、练习、原始代码、图片和项目笔记的唯一内容源。

## 新增或修改内容

1. 在对应的 `*_content-notes/笔记/` 中新增或修改 Markdown。
2. 在同目录的 `import-manifest.yml` 中登记章节、稳定的 `sourceKey`、文章 `slug` 和排序。
3. 如需练习题，维护课程目录下的 `quizzes/`；原始课堂代码和图片保留在相应目录。
4. 在仓库根目录运行 `npm run sync:data`，确认内容数量和校验结果。
5. 运行 `npm run build:pages`。构建通过后提交并推送 `main`，GitHub Actions 会自动部署公开网页。

内容文件必须使用 UTF-8，每篇课程或项目 Markdown 必须只有一个一级标题，代码围栏必须闭合。稳定标识不要随标题修改而改变，否则会影响学习进度、收藏和历史链接的关联。
