#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5, P = 1e9 + 7;
int n, k, m, ans, dp[N][13][1 << 4];
int count(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ++ ans;
    return ans;
}
void cadd(int &x, int y) {x = (x + y) % P;}
signed main() {
    scanf("%d%d%d", &n, &k, &m);
    dp[0][0][0] = 1; int R = (1 << m) - 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= k; ++j)
            for (int mask = 0; mask < 1 << m; ++mask) {
                cadd(dp[i + 1][j][(mask << 1) & R], dp[i][j][mask]);
                if (j < k) 
                    cadd(dp[i + 1][j + 1][((mask << 1) & R) | 1], 1ll * dp[i][j][mask] * (count(mask) + 1) % P);
            }
    for (int mask = 0; mask < 1 << m; ++mask) cadd(ans, dp[n][k][mask]);
    return printf("%d\n", ans), 0;
}