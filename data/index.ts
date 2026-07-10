import snapshot from "./public-data.json";

type RecordLike = Record<string, any>;

const bySortOrder = (a: RecordLike, b: RecordLike) =>
  Number(a.sortOrder ?? 0) - Number(b.sortOrder ?? 0);

export const generatedAt = snapshot.generatedAt;
export const paths = [...snapshot.paths].sort(bySortOrder);
export const courses = [...snapshot.courses].sort(bySortOrder);
export const chapters = [...snapshot.chapters].sort(bySortOrder);
export const articleSummaries = [...snapshot.articleSummaries].sort(bySortOrder);
export const articleDetails = snapshot.articleDetails;
export const projects = [...snapshot.projects].sort(bySortOrder);

export function getPath(id: string) {
  return paths.find((item) => String(item.id) === String(id));
}

export function getCourses(pathId?: string) {
  return courses.filter(
    (item) => !pathId || String(item.pathId) === String(pathId),
  );
}

export function getCourse(id: string) {
  return courses.find((item) => String(item.id) === String(id));
}

export function getChapters(courseId: string) {
  return chapters.filter((item) => String(item.courseId) === String(courseId));
}

export function getChapterArticles(chapterId: string) {
  return articleSummaries.filter(
    (item) => String(item.chapterId) === String(chapterId),
  );
}

export function getArticle(id: string) {
  return articleDetails.find((item) => String(item.article.id) === String(id));
}

export function getArticleNav(id: string) {
  const detail = getArticle(id);
  if (!detail) return { previous: null, next: null };
  const list = getChapterArticles(String(detail.chapterId));
  const index = list.findIndex((item) => String(item.id) === String(id));
  return {
    previous: index > 0 ? list[index - 1] : null,
    next: index >= 0 && index < list.length - 1 ? list[index + 1] : null,
  };
}

export function getProject(id: string) {
  return projects.find((item) => String(item.id) === String(id));
}

export function searchKnowledge(query: string) {
  const keyword = query.trim().toLocaleLowerCase("zh-CN");
  if (!keyword) return { articles: [], projects: [], courses: [] };
  const includes = (...values: unknown[]) =>
    values.some((value) => String(value ?? "").toLocaleLowerCase("zh-CN").includes(keyword));
  return {
    articles: articleDetails
      .filter((item) => includes(item.article.title, item.article.summary, item.article.keywords, item.article.contentMd))
      .map((item) => ({ ...item.article, courseTitle: item.courseTitle, chapterTitle: item.chapterTitle })),
    projects: projects.filter((item) => includes(item.title, item.summary, item.knowledgePoints, item.contentMd)),
    courses: courses.filter((item) => includes(item.title, item.description)),
  };
}
