#include <bits/stdc++.h>
static constexpr int N = 2e3 + 5, P = 1e9 + 7;
int n, m, k, ans;
int sum[N];
int f[N + N][N][2];
 {return (x + y) % P;}
signed main() {
    scanf("%d%d%d", &n, &m, &k);
    int L = n + m - 1;
    f[0][0][0] = 1;
    for (int i = 1; i <= L; ++i) {
        sum[0] = inc(f[i - 1][0][0], f[i - 1][0][1]);
        for (int j = 1; j <= n; ++j) {
            sum[j] = sum[j - 1];
            sum[j] = inc(sum[j], inc(f[i - 1][j][0], f[i - 1][j][1]));
        }
        f[i][0][0] = sum[0];
        for (int j = 1; j <= n; ++j) {
            f[i][j][0] = inc(f[i - 1][j][0], f[i - 1][j][1]);   
            f[i][j][1] = inc(sum[j - 1], P - (j >= k ? sum[j - k] : 0));
        }
        for (int j = 0; j <= n; ++j)
            if (j % (k - 1) == n % (k - 1))
                if ((k - 1) * i - j < m)
                    if (((k - 1) * i - j + 1) % (k - 1) == m % (k - 1))
                        ans = inc(ans, f[i][j][1]);
    } printf("%d\n", ans);
}