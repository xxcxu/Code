#include <bits/stdc++.h>
static constexpr int N = 1e2 + 5, M = 1e5 + 5;
int n, sum;
double m, ans, dp[N][M];
signed main() {
    scanf("%d%lf", &n, &m); m /= 2.0;
    dp[0][0] = 1;
    for (int i = 1, c; i <= n; ++i) {
        scanf("%d", &c); sum += c;
        for (int j = i; j >= 1; --j)
            for (int k = sum; k >= c; --k)
                dp[j][k] += dp[j - 1][k - c] * j / (n - j + 1);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= sum; ++j).
            if (dp[i][j])
                ans = (ans + dp[i][j] * std::min(1.0 * n / i * m + m, 1.0 * j / i));
    printf("%.11lf\n", ans);
}