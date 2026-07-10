import type { Metadata } from "next";
import { headers } from "next/headers";
import { Geist, Geist_Mono, Noto_Sans_SC } from "next/font/google";
import { SiteShell } from "./components/SiteShell";
import "./globals.css";

const sans = Noto_Sans_SC({ variable: "--font-sans", subsets: ["latin"], weight: ["400", "500", "600", "700", "900"] });
const mono = Geist_Mono({ variable: "--font-mono", subsets: ["latin"] });
const display = Geist({ variable: "--font-display", subsets: ["latin"] });

export async function generateMetadata(): Promise<Metadata> {
  const requestHeaders = await headers();
  const host = requestHeaders.get("x-forwarded-host") ?? requestHeaders.get("host") ?? "localhost:3000";
  const protocol = requestHeaders.get("x-forwarded-proto") ?? (host.startsWith("localhost") ? "http" : "https");
  const metadataBase = new URL(`${protocol}://${host}`);
  const description = "从 C 语言、Linux 到 STM32 与嵌入式 AI 的公开学习知识库。";
  return {
    metadataBase,
    title: { default: "嵌入式知识库", template: "%s | 嵌入式知识库" },
    description,
    icons: { icon: "/favicon.svg", shortcut: "/favicon.svg" },
    openGraph: { title: "嵌入式知识库", description, type: "website", images: [{ url: new URL("/og.png", metadataBase), width: 1732, height: 909, alt: "嵌入式知识库" }] },
    twitter: { card: "summary_large_image", title: "嵌入式知识库", description, images: [new URL("/og.png", metadataBase)] },
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
