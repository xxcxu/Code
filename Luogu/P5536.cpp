#include <bits/stdc++.h>
#define eb emplace_back
#define pb pop_back
#define me(a) (std::max_element(a + 1, a + n + 1) - a)
static const int N = 100005;
int n, k, ans_min;
int to[N], dep[N], ans[N], maxdep[N];
std::vector<int> e[N];
void dfs1(int x, int fa) {
    for (int y : e[x]) if (y != fa) {
        dep[y] = dep[x] + 1;
        to[y] = x;
        dfs1(y, x);
    }
}
void dfs2(int x, int fa) {
    maxdep[x] = dep[x];
    for (int y : e[x]) if (y != fa) {
        dep[y] = dep[x] + 1;
        dfs2(y, x);    
        maxdep[x] = std::max(maxdep[x], maxdep[y]);
    }
}
signed main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        e[u].eb(v); e[v].eb(u);
    }
    int rt = 1;
    dep[rt] = 1, dfs1(1, 0), rt = me(dep);
    dep[rt] = 1, dfs1(rt, 0), rt = me(dep);
    int d = dep[rt];
    for (int i = 1; i <= (d - 1) / 2; ++i) rt = to[rt];
    dep[rt] = 1, dfs2(rt, 0);
    for (int i = 1; i <= n; ++i) ans[i] = maxdep[i] - dep[i];
    std::sort(ans + 1, ans + n + 1);
    for (int i = 1; i <= n - k; ++i) ans_min = std::max(ans_min, ans[i] + 1);
    return printf("%d\n", ans_min), 0;
}