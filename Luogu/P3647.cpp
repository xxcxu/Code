#include <bits/stdc++.h>
#define int long long
#define eb emplace_back
using pii = std::pair<int, int>;
static constexpr int N = 2e5 + 5, inf = 1e9;
int n, ans;
int mx1[N], mx2[N], son1[N], son2[N], val[N];
int f[N][2], g[N][2], h[N][2];
std::vector<pii> e[N];
void dfs1(int x, int fa) {
    mx1[x] = mx2[x] = -inf;
    son1[x] = son2[x] = 0;
    for (auto [y, z] : e[x]) if (y != fa) {
        val[y] = z;
        dfs1(y, x);
        f[x][0] += std::max(f[y][0], f[y][1] + z);
        int val = f[y][0] + z - std::max(f[y][0], f[y][1] + z);
        if (mx1[x] < val) {son2[x] = son1[x]; mx2[x] = mx1[x]; son1[x] = y; mx1[x] = val;}
        else if (mx2[x] < val) {son2[x] = y; mx2[x] = val;}
    }
    f[x][1] = f[x][0] + mx1[x];
}
void dfs2(int x, int fa) {
    for (auto [y, z] : e[x]) if (y != fa) {
        if (son1[x] == y) std::swap(mx1[x], mx2[x]), std::swap(son1[x], son2[x]);
        h[x][0] = g[x][0] - std::max(f[y][0], f[y][1] + z);
        h[x][1] = h[x][0] + mx1[x];
        if (fa) h[x][1] = std::max(h[x][1], h[x][0] + h[fa][0] + val[x] - std::max(h[fa][0], h[fa][1] + val[x]));
        g[y][0] = f[y][0] + std::max(h[x][0], h[x][1] + z);
        if (mx1[x] < mx2[x]) std::swap(mx1[x], mx2[x]), std::swap(son1[x], son2[x]);
        dfs2(y, x);
    }
}
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i < n; ++i) {
        static int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        e[u].eb(v, w); e[v].eb(u, w);
    }
    dfs1(1, 0); g[1][0] = f[1][0]; dfs2(1, 0);
    for (int i = 1; i <= n; ++i) ans = std::max(ans, g[i][0]);
    return printf("%lld\n", ans), 0;
}