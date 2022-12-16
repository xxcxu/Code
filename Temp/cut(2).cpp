#include <bits/stdc++.h>
#define eb emplace_back
using pii = std::pair<int, int>;
static constexpr int N = 1e5 + 5, inf = 1e9 + 7;
int n, s, p, col[N], dp[N][3];
std::vector<pii> e[N];
void cadd(int &x, int y) {x = x + y;}
void dfs(int x, int fa) {
    dp[x][0] = dp[x][1] = dp[x][2] = inf;
    dp[x][col[x]] = 0;
    if (!col[x]) dp[x][1] = dp[x][2] = 0;
    for (auto [y, w] : e[x]) if (y != fa) {
        dfs(y, x);
        cadd(dp[x][0], std::min({dp[y][0], dp[y][1] + w, dp[y][2] + w}));
        cadd(dp[x][1], std::min({dp[y][0], dp[y][1], dp[y][2] + w}));
        cadd(dp[x][2], std::min({dp[y][0], dp[y][1] + w, dp[y][2]}));
    }
}
signed main() {
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        static int u, v, z;
        scanf("%d%d%d", &u, &v, &z);
        e[u].eb(v, z); e[v].eb(u, z);
    }
    scanf("%d", &s);
    for (int i = 1; i <= s; ++i) {
        static int x;
        scanf("%d", &x); col[x] = 1;
    }
    scanf("%d", &p);
    for (int i = 1; i <= p; ++i) {
        static int x;
        scanf("%d", &x); col[x] = 2;
    }
    dfs(1, 0);
    printf("%d\n", std::min({dp[1][0], dp[1][1], dp[1][2]}));
}