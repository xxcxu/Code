#include <bits/stdc++.h>
static constexpr int N = 1e3 + 5, M = 1e2 + 5;
int n, m, K, ans, f[N], ten[N];
int dp[N][M];
int pow10(int x, int y) {return 1ll * x * ten[y - 1] % K;}
signed main() {
    freopen("lecture.in", "r", stdin);
    freopen("lecture.out", "w", stdout);
    scanf("%d%d%d", &n, &K, &m);
    dp[0][0] = ten[0] = f[0] = 1; f[1] = 9; 
    for (int i = 1; i <= n; ++i) ten[i] = 1ll * ten[i - 1] * 10ll % K;
    for (int i = 2; i <= n; ++i) f[i] = 1ll * f[i - 1] * 10ll % m;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < K; ++j) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % m;
            for (int k = 1; k <= 9; ++k) {
                int New = (j + pow10(k, i)) % K;
                if (New == 0) ans = (ans + 1ll * dp[i - 1][j] * f[n - i] % m) % m;
                else dp[i][New] = (dp[i][New] + dp[i - 1][j]) % m;
            } 
        }
    printf("%d\n", ans);
    return 0;
}