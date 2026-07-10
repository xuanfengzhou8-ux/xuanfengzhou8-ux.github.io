import Link from "next/link";
import { getCourses, paths } from "../../data";

export const metadata = { title: "课程知识库" };

export default async function CoursesPage({ searchParams }: { searchParams: Promise<{ pathId?: string }> }) {
  const { pathId } = await searchParams;
  const selectedPath = paths.find((item) => String(item.id) === String(pathId ?? ""));
  const list = getCourses(pathId);
  return (
    <div className="page-width content-page">
      <header className="page-header"><span>COURSE INDEX</span><h1>课程知识库</h1><p>按学习路径筛选，找到适合你当前阶段的课程。</p></header>
      <nav className="filter-bar" aria-label="课程路径筛选"><Link className={!pathId ? "active" : ""} href="/courses">全部</Link>{paths.map((path) => <Link className={String(path.id) === pathId ? "active" : ""} href={`/courses?pathId=${path.id}`} key={path.id}>{path.name}</Link>)}</nav>
      <div className="list-meta"><strong>{selectedPath?.name ?? "全部课程"}</strong><span>共 {list.length} 门</span></div>
      <div className="catalog-grid">
        {list.map((course, index) => <Link className="catalog-card" href={`/courses/${course.id}`} key={course.id}><span>{String(index + 1).padStart(2, "0")}</span><small>{course.level}</small><h2>{course.title}</h2><p>{course.description}</p><b>查看课程 →</b></Link>)}
      </div>
    </div>
  );
}
