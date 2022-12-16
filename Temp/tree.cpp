#include <bits/stdc++.h>
static constexpr int N = 3e5 + 5, M = 5e3 + 5;
int n;
int dep[N];
int anc[N][26], dis[M][M];
std::vector<int> e[N];
void dfs(int x, int fa) {
    anc[x][0] = fa;
    for (int i = 1; i <= 25; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    dep[x] = dep[fa] + 1;
    for (int y : e[x]) if (y != fa) dfs(y, x);
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = 25; i >= 0; --i)
        if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (int i = 25; i >= 0; --i)
        if (anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}
int gcd(int x, int y) {return !y ? x : gcd(y, x % y);}
signed main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            dis[i][j] = dep[i] + dep[j] - 2 * dep[lca(i, j)];
    using ll = long long;
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            ans += gcd(i, gcd(j, dis[i][j]));
    printf("%lld\n", ans * 2 + 1ll * n * (n + 1) / 2);
    return 0;
}