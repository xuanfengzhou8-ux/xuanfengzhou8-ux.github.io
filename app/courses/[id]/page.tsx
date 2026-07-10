import Link from "next/link";
import { notFound } from "next/navigation";
import { getChapterArticles, getChapters, getCourse } from "../../../data";

export default async function CourseDetailPage({ params }: { params: Promise<{ id: string }> }) {
  const { id } = await params;
  const course = getCourse(id);
  if (!course) notFound();
  const chapterList = getChapters(id);
  const articleCount = chapterList.reduce((sum, chapter) => sum + getChapterArticles(String(chapter.id)).length, 0);
  return (
    <>
      <header className="course-hero"><div className="page-width"><p><Link href="/courses">课程</Link> / {course.title}</p><span>{course.level}</span><h1>{course.title}</h1><h2>{course.description}</h2><dl><div><dt>{chapterList.length}</dt><dd>个章节</dd></div><div><dt>{articleCount}</dt><dd>篇文章</dd></div></dl></div></header>
      <div className="page-width course-content"><h2>课程目录</h2>
        <div className="chapter-list">{chapterList.map((chapter, index) => { const list = getChapterArticles(String(chapter.id)); return <section className="chapter-block" key={chapter.id}><header><span>{String(index + 1).padStart(2, "0")}</span><div><h3>{chapter.title}</h3>{chapter.description && <p>{chapter.description}</p>}</div><small>{list.length} 篇</small></header><div>{list.map((article) => <Link href={`/articles/${article.id}`} key={article.id}><span>□</span><strong>{article.title}</strong><b>阅读 →</b></Link>)}</div></section>; })}</div>
      </div>
    </>
  );
}
