import { Suspense } from "react";
import { CoursesCatalog } from "./CoursesCatalog";

export const metadata = { title: "课程知识库" };

export default function CoursesPage() {
  return <Suspense><CoursesCatalog /></Suspense>;
}
