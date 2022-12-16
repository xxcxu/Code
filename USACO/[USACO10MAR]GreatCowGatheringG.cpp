#include <bits/stdc++.h>
#define int long long
using pii = std::pair<int, int>;
const int N = 1e5 + 5;
int n, sum, ans, c[N], f[N], size[N], g[N];
std::vector<pii> Graph[N];
void Dfs(int x, int fa) {
    size[x] = c[x];
    for (pii node : Graph[x]) {
        int y = node.first, link = node.second;
        if (y == fa) continue;
        Dfs(y, x); size[x] += size[y];
        f[x] += f[y] + size[y] * link;
    } return void();
} 
void Dfs2(int x, int fa) {
    for (pii node : Graph[x]) {
        int y = node.first, link = node.second;
        if (y == fa) continue;
        g[y] = g[x] + (sum - 2 * size[y]) * link;
        ans = std::min(ans, g[y]);
        Dfs2(y, x);
    } return void();
}
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", c + i), sum += c[i];
    for (int i = 1, u, v, w; i < n; ++i) {
        scanf("%lld%lld%lld", &u, &v, &w);
        Graph[u].emplace_back(pii(v, w));
        Graph[v].emplace_back(pii(u, w));
    } Dfs(1, 0); ans = LONG_LONG_MAX; g[1] = f[1]; Dfs2(1, 0);
    return printf("%lld\n", ans), 0;
}
