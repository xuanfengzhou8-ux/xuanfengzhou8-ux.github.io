import Link from "next/link";
import { searchKnowledge } from "../../data";

export const metadata = { title: "搜索" };

export default async function SearchPage({ searchParams }: { searchParams: Promise<{ q?: string }> }) {
  const { q = "" } = await searchParams;
  const result = searchKnowledge(q);
  const total = result.articles.length + result.projects.length + result.courses.length;
  return <div className="page-width content-page"><header className="page-header compact"><span>SEARCH</span><h1>搜索知识库</h1></header><form className="search-page-form" action="/search"><input name="q" defaultValue={q} placeholder="搜索标题、知识点或关键词…" autoFocus /><button>搜索</button></form>{q && <p className="search-summary">关键词「<strong>{q}</strong>」找到 {total} 项结果</p>}<div className="search-results">{result.courses.map((item) => <Link href={`/courses/${item.id}`} key={`course-${item.id}`}><span>课程</span><div><h2>{item.title}</h2><p>{item.description}</p></div><b>→</b></Link>)}{result.articles.map((item) => <Link href={`/articles/${item.id}`} key={`article-${item.id}`}><span>文章</span><div><h2>{item.title}</h2><p>{item.summary || `${item.courseTitle} / ${item.chapterTitle}`}</p></div><b>→</b></Link>)}{result.projects.map((item) => <Link href={`/projects/${item.id}`} key={`project-${item.id}`}><span>项目</span><div><h2>{item.title}</h2><p>{item.summary}</p></div><b>→</b></Link>)}</div>{q && total === 0 && <div className="empty-state"><b>∅</b><h2>没有找到相关内容</h2><p>请尝试更短的关键词或课程名称。</p></div>}</div>;
}
