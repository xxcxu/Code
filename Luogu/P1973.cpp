#include <bits/stdc++.h>

static constexpr int N = 5e2 + 5, inf = 0x3f3f3f3f;
int n, m, ans;
int a[N], l[N], r[N];
int f[N][N], g[N][N], h[N][N], c[N][N], vis[N][N];

signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        static int s, t;
        scanf("%d%d", &s, &t);
        a[++ m] = l[i] = s;
        a[++ m] = r[i] = s + t - 1;
    }
    std::sort(a + 1, a + m + 1);
    for (int i = 1; i <= n; ++i) {
        l[i] = std::lower_bound(a + 1, a + m + 1, l[i]) - a;
        r[i] = std::lower_bound(a + 1, a + m + 1, r[i]) - a;
        if (vis[l[i]][r[i]]) ++ r[i];
        vis[l[i]][r[i]] = true;
    }
    for (int i = 1; i <= m; ++i)
        for (int j = i; j <= m; ++j)
            for (int k = 1; k <= n; ++k)
                if (l[k] >= i && r[k] <= j) ++ c[i][j]; 
    std::memset(f, -0x3f, sizeof f);
    std::memset(g, -0x3f, sizeof g);
    g[m + 1][0] = f[0][0] = 0;
    for (int i = 1; i <= m; ++i)
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k < i; ++k)
                f[i][j] = std::max({f[i][j], f[k][j] + c[k + 1][i], j >= c[k + 1][i] ? f[k][j - c[k + 1][i]] : -inf});
	for (int i = m; i; --i)
        for (int j = 0; j <= n; ++j)
            for (int k = i + 1; k <= m + 1; ++k)
                g[i][j] = std::max({g[i][j], g[k][j] + c[i][k - 1], j >= c[i][k - 1] ? g[k][j - c[i][k - 1]] : -inf});
    for (int i = 0; i <= n; ++i) ans = std::max(ans, std::min(i, f[m][i]));
    printf("%d\n", ans);
    for (int i = 1; i <= m; ++i)
        for (int j = i; j <= m; ++j)
            for (int x = 0, y = m; x <= n && f[i - 1][x] >= 0; ++x) {
                while (y && std::min(f[i - 1][x] + g[j + 1][y], x + y + c[i][j]) <= std::min(f[i - 1][x] + g[j + 1][y - 1], x + y - 1 + c[i][j])) -- y;
                h[i][j] = std::max(h[i][j], std::min(f[i - 1][x] + g[j + 1][y], x + y + c[i][j]));
            }
    for (int x = 1; x <= n; ++x) {
        ans = 0;
        for (int i = 1; i <= l[x]; ++i)
            for (int j = r[x]; j <= m; ++j)
                ans = std::max(ans, h[i][j]);
        printf("%d\n", ans);
    }
    return 0;
}