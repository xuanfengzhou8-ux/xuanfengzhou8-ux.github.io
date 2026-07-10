import Link from "next/link";

export function SiteShell({ children }: { children: React.ReactNode }) {
  return (
    <div className="site-shell">
      <header className="site-header">
        <div className="header-inner">
          <Link className="brand" href="/" aria-label="嵌入式知识库首页">
            <span className="brand-mark" aria-hidden="true"><i /><i /><i /></span>
            <span><strong>EMBEDDED</strong><small>KNOWLEDGE BASE</small></span>
          </Link>
          <nav className="main-nav" aria-label="主导航">
            <Link href="/paths">学习路径</Link>
            <Link href="/courses">课程</Link>
            <Link href="/projects">项目实战</Link>
          </nav>
          <form className="header-search" action="/search" role="search">
            <input name="q" type="search" placeholder="搜索知识点…" aria-label="搜索知识库" />
            <button type="submit" aria-label="提交搜索">→</button>
          </form>
          <span className="public-badge"><i /> 公开阅读</span>
        </div>
      </header>
      <main>{children}</main>
      <footer className="site-footer">
        <div><strong>Embedded Knowledge Base</strong><span>为嵌入式学习建立清晰路径</span></div>
        <span>公开只读版</span>
      </footer>
    </div>
  );
}
