#include <bits/stdc++.h>
static constexpr int N = 5e2 + 5;
int n, K, a[N];
double f[N][N], g[N][N], h[N][N];
auto main() -> decltype(0) {
    freopen("battle.in", "r", stdin);
    freopen("battle.out", "w", stdout);
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i), f[i][i] = g[i][i] = h[i][i] = 1.0;
    for (int len = 2; len <= n; ++len)
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            for (int i = l; i < r; ++i) h[l][r] += f[l][i] * g[i + 1][r];
            for (int i = l + 1; i <= r; ++i) f[l][r] += h[l][i] * f[i][r] * a[l] * 1.0 / (a[l] + a[i]);
            for (int i = l; i <= r - 1; ++i) g[l][r] += g[l][i] * h[i][r] * a[r] * 1.0 / (a[r] + a[i]);
            f[l][r] *= 1.0 / (r - l);
            g[l][r] *= 1.0 / (r - l);
        }
    return printf("%.17lf\n", g[1][K] * f[K][n]), 0;
}