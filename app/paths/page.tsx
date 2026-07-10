import Link from "next/link";
import { getCourses, paths } from "../../data";

export const metadata = { title: "学习路径" };

export default function PathsPage() {
  return (
    <div className="page-width content-page">
      <header className="page-header"><span>LEARNING MAP</span><h1>嵌入式学习路径</h1><p>建议按编号顺序推进，已有基础的同学也可从对应课程切入。</p></header>
      <div className="timeline">
        {paths.map((path, index) => (
          <section className="timeline-item" key={path.id}>
            <span className="timeline-number">0{index + 1}</span>
            <div><h2>{path.name}</h2><p>{path.description}</p>
              <div className="timeline-courses">
                {getCourses(String(path.id)).map((course, courseIndex) => (
                  <Link href={`/courses/${course.id}`} key={course.id}><span>{courseIndex + 1}</span><strong>{course.title}</strong><small>{course.level}</small><b>进入 →</b></Link>
                ))}
              </div>
            </div>
          </section>
        ))}
      </div>
    </div>
  );
}
