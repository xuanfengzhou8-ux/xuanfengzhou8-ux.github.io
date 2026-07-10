import Link from "next/link";
import { projects } from "../../data";

export const metadata = { title: "项目实战" };

export default function ProjectsPage() {
  return <div className="page-width content-page"><header className="page-header"><span>PROJECT LAB</span><h1>项目实战</h1><p>用真实需求串联知识点，从最小可用功能开始逐步完善。</p></header><div className="project-list">{projects.map((project, index) => <Link href={`/projects/${project.id}`} key={project.id}><span>{String(index + 1).padStart(2, "0")}</span><div><small>{project.difficulty}</small><h2>{project.title}</h2><p>{project.summary}</p><b>{project.knowledgePoints}</b></div><i>↗</i></Link>)}</div></div>;
}
