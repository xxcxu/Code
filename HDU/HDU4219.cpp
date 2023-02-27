#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define eb emplace_back
static const int N = 65, S = 513;
int n, l, s, Case;
double dp[N][S];
std::vector<int> e[N];
double g[S], h[S];
void dfs(int x, int fa) {
    dp[x][0] = 1;
    for (int y : e[x]) if (y != fa) {
        dfs(y, x);
        std::memset(g, 0, sizeof g);
        std::memset(h, 0, sizeof h);
        for (int i = 0; i <= l; ++i)    
            for (int j = 0; j <= s; ++j)
                if (i + j <= s) g[i + j] += 1.0 * dp[y][j] / (l + 1);
        for (int i = 0; i <= s; ++i)
            for (int j = 0; j <= s; ++j)
                if (i + j <= s) h[std::max(i, j)] += dp[x][j] * g[i];
        for (int i = 0; i <= s; ++i) dp[x][i] = h[i];
    }
    return void();
}
signed main() {
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &l, &s);
        for (int i = 1; i <= n; ++i) e[i].clear();
        for (int i = 1; i <  n; ++i) {
            scanf("%d%d", &u, &v);
            e[u].eb(v); e[v].eb(u);
        }
        std::memset(dp, 0, sizeof dp);
        dfs(1, -1);
        double ans = 0.0;
        for (int i = 0; i <= s; ++i) ans += dp[1][i];
        printf("Case %d: %.6lf\n", ++ Case, ans);
    }
    return 0;
}