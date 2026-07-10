import type { Metadata } from "next";
import { Geist, Geist_Mono, Noto_Sans_SC } from "next/font/google";
import { SiteShell } from "./components/SiteShell";
import "./globals.css";

const sans = Noto_Sans_SC({ variable: "--font-sans", subsets: ["latin"], weight: ["400", "500", "600", "700", "900"] });
const mono = Geist_Mono({ variable: "--font-mono", subsets: ["latin"] });
const display = Geist({ variable: "--font-display", subsets: ["latin"] });

export function generateMetadata(): Metadata {
  const isGitHubPages = process.env.GITHUB_PAGES === "true";
  const metadataBase = new URL(isGitHubPages
    ? "https://xuanfengzhou8-ux.github.io/"
    : "https://embedded-kb-public.xuanfengzhou8.chatgpt.site/");
  const imageUrl = new URL("og.png", metadataBase);
  const description = "从 C 语言、Linux 到 STM32 与嵌入式 AI 的公开学习知识库。";
  return {
    metadataBase,
    title: { default: "嵌入式知识库", template: "%s | 嵌入式知识库" },
    description,
    icons: { icon: "/favicon.svg", shortcut: "/favicon.svg" },
    openGraph: { title: "嵌入式知识库", description, type: "website", images: [{ url: imageUrl, width: 1732, height: 909, alt: "嵌入式知识库" }] },
    twitter: { card: "summary_large_image", title: "嵌入式知识库", description, images: [imageUrl] },
  };
}

export default function RootLayout({ children }: Readonly<{ children: React.ReactNode }>) {
  return (
    <html lang="zh-CN">
      <body className={`${sans.variable} ${mono.variable} ${display.variable}`}>
        <SiteShell>{children}</SiteShell>
      </body>
    </html>
  );
}
