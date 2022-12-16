#include <bits/stdc++.h>
#define eb emplace_back
static constexpr int N = 2e6 + 5;
int n, m, scc_cnt;
int dfn[N], size[N];
std::vector<int> e[N], v[N];
void tarjan(int x, int fa) {
    static int time_stamp = 0, top = 0;
    static int instack[N], stack[N], low[N];

    dfn[x] = low[x] = ++ time_stamp;
    instack[x] = true; stack[++ top] = x;

    for (auto y : e[x]) {
        if (y == fa) continue;
        if (!dfn[y]) tarjan(y, x), low[x] = std::min(low[x], low[y]);
        else if (instack[y]) low[x] = std::min(low[x], dfn[y]);
    }

    if (dfn[x] == low[x]) {
        int u;
        ++ scc_cnt;
        do {
            u = stack[top --];
            ++ size[scc_cnt];
            v[scc_cnt].eb(u);
            instack[u] = false;
        } while (u != x);
    }
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        e[u].eb(v); e[v].eb(u);
    }
    for (int i = 1; i <= n; ++i) {
        std::sort(e[i].begin(), e[i].end());
        e[i].erase(std::unique(e[i].begin(), e[i].end()), e[i].end());
    }
    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i, 0);
    printf("%d\n", scc_cnt);
    for (int i = 1; i <= scc_cnt; ++i) {
        printf("%d ", size[i]);
        for (int j : v[i]) printf("%d ", j);
        puts("");
    }
    return 0;
}