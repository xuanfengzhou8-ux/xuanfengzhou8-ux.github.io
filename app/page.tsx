import Link from "next/link";
import { courses, paths, projects, articleDetails } from "../data";

export default function Home() {
  return (
    <>
      <section className="hero">
        <div className="signal-grid" aria-hidden="true" />
        <div className="hero-orbit" aria-hidden="true"><i /><i /><i /><span>KB</span></div>
        <div className="hero-inner page-width">
          <div className="hero-copy">
            <p className="eyebrow"><i /> KNOWLEDGE SYSTEM / PUBLIC</p>
            <h1>把零散知识，连成<br /><span>真正走得通的路径。</span></h1>
            <p className="hero-lead">从 C 语言、Linux 到 STM32 与嵌入式 AI，按知识前置关系组织课程、文章和项目。</p>
            <div className="hero-actions">
              <Link className="button primary" href="/paths">开始阅读 <span>→</span></Link>
              <Link className="button secondary" href="/projects">浏览项目</Link>
            </div>
          </div>
          <div className="hero-console">
            <p>知识库内容已就绪</p>
            <dl>
              <div><dt>{paths.length}</dt><dd>学习路径</dd></div>
              <div><dt>{courses.length}</dt><dd>门课程</dd></div>
              <div><dt>{articleDetails.length}</dt><dd>篇文章</dd></div>
              <div><dt>{projects.length}</dt><dd>个项目</dd></div>
            </dl>
            <form action="/search" role="search">
              <input name="q" placeholder="搜索指针、GPIO、FreeRTOS…" aria-label="搜索知识库" />
              <button type="submit">搜索</button>
            </form>
          </div>
        </div>
      </section>

      <section className="section page-width">
        <div className="section-heading"><div><span>LEARNING MAP</span><h2>五条学习路径</h2></div><Link href="/paths">查看全部 →</Link></div>
        <p className="section-lead">按前置关系安排，让每个知识点都知道自己从哪里来、向哪里去。</p>
        <div className="path-grid">
          {paths.map((path, index) => (
            <Link className="path-card" href={`/courses?pathId=${path.id}`} key={path.id}>
              <span className="card-index">0{index + 1}</span><h3>{path.name}</h3><p>{path.description}</p><b>进入路径 ↗</b>
            </Link>
          ))}
        </div>
      </section>

      <section className="section section-dark">
        <div className="page-width">
          <div className="section-heading inverse"><div><span>COURSE INDEX</span><h2>推荐课程</h2></div><Link href="/courses">浏览全部 →</Link></div>
          <div className="course-grid">
            {courses.slice(0, 6).map((course, index) => (
              <Link className={index === 0 ? "course-card featured" : "course-card"} href={`/courses/${course.id}`} key={course.id}>
                <span>{course.level === "BEGINNER" ? "入门" : course.level === "INTERMEDIATE" ? "进阶" : "高级"}</span>
                <h3>{course.title}</h3><p>{course.description}</p><b>进入课程 →</b>
              </Link>
            ))}
          </div>
        </div>
      </section>

      <section className="section page-width">
        <div className="section-heading"><div><span>PROJECT LAB</span><h2>从项目反推知识</h2></div><Link href="/projects">查看全部 →</Link></div>
        <div className="project-grid">
          {projects.map((project) => (
            <Link className="project-card" href={`/projects/${project.id}`} key={project.id}>
              <span className="project-symbol">⌁</span><div><small>{project.difficulty}</small><h3>{project.title}</h3><p>{project.summary}</p><b>{project.knowledgePoints}</b></div>
            </Link>
          ))}
        </div>
      </section>
    </>
  );
}
