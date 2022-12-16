#include <bits/stdc++.h>
#define int long long
static constexpr int N = 1e6 + 5;
int n, r1, r2, r3, d;
int a[N], dp[N][2];
signed main() {
    scanf("%lld%lld%lld%lld%lld", &n, &r1, &r2, &r3, &d);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    dp[0][1] = -d;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[i - 1][1] + d + std::min(r2, r1 * a[i] + r1);
        dp[i][1] = std::min(
            dp[i - 1][1] + d + r1 * a[i] + r3, 
            dp[i - 1][0] + d + std::min(r1 * a[i] + std::min(r1 * 2, r3), r2 + r1) + d + r1 + d
        );
    }
    dp[n][1] = std::min(
        dp[n - 1][1] + d + r1 * a[n] + r3, 
        dp[n - 1][0] + d + std::min(r1 * a[n] + std::min(r1 * 2 + d, r3), r2 + r1 + d) + r1 + d
    );
    printf("%lld\n", std::min(dp[n][1], dp[n][0] + d + d + r1));
    return 0;
}
