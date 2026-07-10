import Link from "next/link";
import { notFound } from "next/navigation";
import { getProject, projects } from "../../../data";
import { MarkdownArticle } from "../../components/MarkdownArticle";

export function generateStaticParams() {
  return projects.map((project) => ({ id: String(project.id) }));
}

export default async function ProjectPage({ params }: { params: Promise<{ id: string }> }) {
  const { id } = await params;
  const project = getProject(id);
  if (!project) notFound();
  return <div className="page-width project-detail"><nav className="breadcrumbs"><Link href="/projects">项目实战</Link><span>/</span><span>{project.title}</span></nav><header><span>{project.difficulty}</span><h1>{project.title}</h1><p>{project.summary}</p><div>{String(project.knowledgePoints ?? "").split(",").map((item: string) => <small key={item}>{item}</small>)}</div></header><section className="reading-card"><MarkdownArticle content={project.contentMd} /></section></div>;
}
