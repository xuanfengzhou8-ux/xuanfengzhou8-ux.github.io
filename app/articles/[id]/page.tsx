import Link from "next/link";
import { notFound } from "next/navigation";
import { articleDetails, getArticle, getArticleNav } from "../../../data";
import { MarkdownArticle } from "../../components/MarkdownArticle";

export function generateStaticParams() {
  return articleDetails.map((detail) => ({ id: String(detail.article.id) }));
}

export default async function ArticlePage({ params }: { params: Promise<{ id: string }> }) {
  const { id } = await params;
  const detail = getArticle(id);
  if (!detail) notFound();
  const nav = getArticleNav(id);
  return (
    <div className="reading-page page-width">
      <article className="reading-card">
        <nav className="breadcrumbs"><Link href={`/courses?pathId=${detail.pathId}`}>{detail.pathName}</Link><span>/</span><Link href={`/courses/${detail.courseId}`}>{detail.courseTitle}</Link><span>/</span><span>{detail.chapterTitle}</span></nav>
        <header className="article-header"><p>ARTICLE / {detail.article.id}</p><h1>{detail.article.title}</h1>{detail.article.summary && <h2>{detail.article.summary}</h2>}<div>{String(detail.article.keywords ?? "").split(",").filter(Boolean).map((keyword: string) => <span key={keyword}>{keyword}</span>)}</div></header>
        <MarkdownArticle content={detail.article.contentMd} />
        <nav className="prev-next"><div>{nav.previous ? <Link href={`/articles/${nav.previous.id}`}><small>← 上一篇</small><strong>{nav.previous.title}</strong></Link> : <span />}</div><div>{nav.next ? <Link href={`/articles/${nav.next.id}`}><small>下一篇 →</small><strong>{nav.next.title}</strong></Link> : <span />}</div></nav>
      </article>
      <aside className="reading-rail"><div><span>PUBLIC READING</span><h2>公开只读内容</h2><p>无需登录即可阅读。学习进度、收藏和 AI 问答不会保存。</p></div><Link href={`/courses/${detail.courseId}`}>返回课程目录 →</Link></aside>
    </div>
  );
}
