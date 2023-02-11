#include <bits/stdc++.h>
static const int N = 13, inf = 2147483647;
int n, m;
int f[1 << N][1 << N], g[N][1 << N];
int a[N][N];
int lowbit(int x) {return (x) & (-x);}
int calc(int x, int S) {
    int min = inf;
    for (int i = 0; i < n; ++i) 
        if (S >> i & 1)
            min = std::min(min, a[i][x]);
    return min;
}
signed main() {
    scanf("%d%d", &n, &m);
    std::memset(a, 1, sizeof a);
    std::memset(g, 63, sizeof g);
    for (int i = 0; i < m; ++i) {
        static int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        -- u; -- v;
        if (a[u][v] > w) a[u][v] = a[v][u] = w;
    }
    int R = 1 << n, S = R - 1;
    for (int i = 1; i < R; ++i) {
        int res = i ^ S;
        std::vector<int> subset; subset.clear();
        for (int j = res; j; j = (j - 1) & res) subset.emplace_back(j);
        std::reverse(subset.begin(), subset.end());
        for (int j : subset) {
            int x = lowbit(j), sta = j ^ x;
            x = (int)std::log2(x);
            f[i][j] = f[i][sta] + calc(x, i);
        }
    }
    for (int i = 1; i < R; i <<= 1) g[0][i] = 0;
    for (int h = 1; h <= n; ++h)
        for (int i = 1; i < R; ++i)
            for (int j = i; j; j = (j - 1) & i)
                g[h][i] = std::min(g[h][i], g[h - 1][i ^ j] + f[i ^ j][j] * h);
    int ans = inf;
    for (int h = 0; h <= n; ++h) ans = std::min(ans, g[h][S]);
    return printf("%d\n", ans), 0;
}