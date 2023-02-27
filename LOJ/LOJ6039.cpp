#include <bits/stdc++.h>
#define int long long
#define eb emplace_back
static const int N = 305, M = 50005;
int n, m;
std::vector<int> e[N];
int dp[N][M];
void solve(int l, int r, int ql, int qr, int j, int x, int y) {
    if (l > r || ql > qr) return void();
    int mid = (l + r) >> 1, p = 0;
    int s = std::max(ql, mid - (int)e[j].size() + 1);
    int t = std::min(qr, mid);
    for (int i = s; i <= t; ++i) {
        if (dp[j][x * mid + y] < dp[j - 1][x * i + y] + e[j][mid - i])
            dp[j][x * mid + y] = dp[j - 1][x * i + y] + e[j][mid - i], p = i;
    }
    solve(l, mid - 1, ql, p, j, x, y);
    solve(mid + 1, r, p, qr, j, x, y);
}
signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= 300; ++i) e[i].eb(0);
    for (int i = 1; i <= n; ++i) {
        static int c, v;
        scanf("%lld%lld", &c, &v);
        e[c].eb(v);
    }
    for (int i = 1; i <= 300; ++i) {
        std::sort(e[i].begin() + 1, e[i].end(), [&](int a, int b) {return a > b;});
        for (int j = 1; j < (int)e[i].size(); ++j) e[i][j] += e[i][j - 1];
    }
    for (int i = 1; i <= 300; ++i) {
        for (int j = 0; j < i; ++ j) solve(1, (m - j) / i, 0, (m - j) / i, i, i, j);
        for (int j = 0; j <= m; ++j) dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
    }
    for (int i = 1; i <= m; ++i) printf("%lld ", dp[300][i]);
    return 0;
}