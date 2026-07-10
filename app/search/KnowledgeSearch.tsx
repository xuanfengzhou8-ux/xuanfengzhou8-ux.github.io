"use client";

import Link from "next/link";
import { FormEvent, useMemo, useState } from "react";
import { useRouter, useSearchParams } from "next/navigation";
import index from "../../data/search-index.json";

const matches = (query: string, ...values: unknown[]) => values.some((value) => String(value ?? "").toLocaleLowerCase("zh-CN").includes(query));

export function KnowledgeSearch() {
  const router = useRouter();
  const initialQuery = useSearchParams().get("q") ?? "";
  const [input, setInput] = useState(initialQuery);
  const query = initialQuery.trim().toLocaleLowerCase("zh-CN");
  const result = useMemo(() => ({
    courses: query ? index.courses.filter((item) => matches(query, item.title, item.description)) : [],
    articles: query ? index.articles.filter((item) => matches(query, item.title, item.summary, item.keywords, item.courseTitle, item.chapterTitle)) : [],
    projects: query ? index.projects.filter((item) => matches(query, item.title, item.summary, item.knowledgePoints)) : [],
  }), [query]);
  const total = result.articles.length + result.projects.length + result.courses.length;
  function submit(event: FormEvent) { event.preventDefault(); router.push(`/search?q=${encodeURIComponent(input.trim())}`); }

  return <div className="page-width content-page"><header className="page-header compact"><span>SEARCH</span><h1>搜索知识库</h1></header><form className="search-page-form" onSubmit={submit}><input value={input} onChange={(event) => setInput(event.target.value)} placeholder="搜索标题、知识点或关键词…" autoFocus /><button>搜索</button></form>{initialQuery && <p className="search-summary">关键词「<strong>{initialQuery}</strong>」找到 {total} 项结果</p>}<div className="search-results">{result.courses.map((item) => <Link href={`/courses/${item.id}`} key={`course-${item.id}`}><span>课程</span><div><h2>{item.title}</h2><p>{item.description}</p></div><b>→</b></Link>)}{result.articles.map((item) => <Link href={`/articles/${item.id}`} key={`article-${item.id}`}><span>文章</span><div><h2>{item.title}</h2><p>{item.summary || `${item.courseTitle} / ${item.chapterTitle}`}</p></div><b>→</b></Link>)}{result.projects.map((item) => <Link href={`/projects/${item.id}`} key={`project-${item.id}`}><span>项目</span><div><h2>{item.title}</h2><p>{item.summary}</p></div><b>→</b></Link>)}</div>{initialQuery && total === 0 && <div className="empty-state"><b>∅</b><h2>没有找到相关内容</h2><p>请尝试更短的关键词或课程名称。</p></div>}</div>;
}
