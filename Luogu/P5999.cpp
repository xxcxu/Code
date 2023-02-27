#include <bits/stdc++.h>
static const int N = 2005, P = 1000000007;
int n, s, t;
int dp[N][N];
int inc(int x, int y) {return (x + y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}
signed main() {
    scanf("%d%d%d", &n, &s, &t);
    dp[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == s || i == t) {
                dp[i][j] = inc(dp[i][j], dp[i - 1][j]);
                dp[i][j] = inc(dp[i][j], dp[i - 1][j - 1]);
                continue;
            }
            int c = (i > s) + (i > t);
            dp[i][j] = inc(dp[i][j], mul(dp[i - 1][j - 1],  j - c));
            dp[i][j] = inc(dp[i][j], mul(dp[i - 1][j + 1],  j));
        }
    }
    return printf("%d\n", dp[n][1]), 0;
}