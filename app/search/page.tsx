import { Suspense } from "react";
import { KnowledgeSearch } from "./KnowledgeSearch";

export const metadata = { title: "搜索" };

export default function SearchPage() {
  return <Suspense><KnowledgeSearch /></Suspense>;
}
