#include <bits/stdc++.h>

static constexpr int N = 2e5 + 5;

using pii = std::pair<int, int>;
int scc_cnt;
int dfn[N], col[N], bel[N];
std::vector<pii> g[N];

int cnt = -1;
int head[N];
class edge {
    public: int from, to, link, next;
    public: edge(int from = 0, int to = 0, int link = 0, int next = 0):
        from(from), to(to), link(link), next(next) {}
} e[N << 1];

void add(int u, int v, int w) {
    e[++ cnt] = edge(u, v, w, head[u]); head[u] = cnt;
}

void tarjan(int x, int id) {
    static int time_stamp = 0, top = 0;
    static int instack[N], stack[N], low[N];

    col[x] = col[0];
    dfn[x] = low[x] = ++ time_stamp;
    instack[x] = true; stack[++ top] = x;

    for (int i = head[x]; ~i; i = e[i].next) {
        const int &y = e[i].to, &z = e[i].link;
        if ((i ^ 1) == id) continue;
        if (!dfn[y]) tarjan(y, i), low[x] = std::min(low[x], low[y]);
        else if (instack[y]) low[x] = std::min(low[x], dfn[y]);
    }
    
    if (dfn[x] == low[x]) {
        int u = 0; ++ scc_cnt;
        while (u != x) {
            u = stack[top --];
            bel[u] = scc_cnt;
            instack[u] = false;
        }
    }
}

int n, m, q;
int s[N], t[N], f[N], dp[N], dep[N], vis[N], anc[N][32];

void dfs1(int x, int pre) {
    dep[x] = dep[pre] + 1;
    anc[x][0] = pre;
    for (int i = 1; i <= 25; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (auto &[y, z] : g[x]) {
        if (y == pre) continue;
        dfs1(y, x);
    }
}

void dfs2(int x) {
    vis[x] = true;
    for (auto &[y, z] : g[x]) {
        if (y == anc[x][0]) continue;
        dfs2(y);
        f[x] += f[y];
        dp[x] += dp[y];
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = 25; ~i; --i)
        if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (int i = 25; ~i; --i)
        if (anc[x][i] != anc[y][i]) 
            x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}

signed main() {
    scanf("%d%d%d", &n, &m, &q);
    std::memset(head, -1, (n + 1) * sizeof(int));
    for (int i = 1; i <= m; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        add(u, v, 1);
        add(v, u, 1);
    }
    for (int i = 1; i <= q; ++i) scanf("%d%d", s + i, t + i);
    for (int i = 1; i <= n; ++i) 
        if (!dfn[i]) {
            ++ col[0];
            tarjan(i, -1);
        }
    for (int i = 1; i <= n; ++i) {
        for (int j = head[i]; ~j; j = e[j].next) {
            const int &k = e[j].to, &w = e[j].link;
            if (bel[i] != bel[k]) g[bel[i]].emplace_back(bel[k], w);
        }
    }
    for (int i = 1; i <= n; ++i) if (!dep[i]) dfs1(i, 0);
    for (int i = 1; i <= q; ++i) {
        if (col[s[i]] != col[t[i]]) return puts("No"), 0;
        s[i] = bel[s[i]], t[i] = bel[t[i]];
        int L = lca(s[i], t[i]);
        ++ f[s[i]], -- f[L];
        ++ dp[t[i]], -- dp[L];
    }   
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs2(i);
    for (int i = 1; i <= n; ++i) if (f[i] && dp[i]) return puts("No"), 0;
    return puts("Yes"), 0;
}