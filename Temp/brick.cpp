#include <bits/stdc++.h>
static constexpr int N = 5e3 + 5;
int n, ans, a[N], dp[N][N];
void cmin(int &x, int y) {if (y < x) x = y;}
void cmax(int &x, int y) {if (y > x) x = y;}
signed main() {
    freopen("brick.in", "r", stdin);
    freopen("brick.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    dp[1][1] = 0;
    for (int r = 1; r < n; ++r) {
        for (int l = 1; l <= r; ++l) cmax(dp[l][r], dp[l - 1][r]);
        int l = r, sum = 0, cnt = 0, max = 0;
        for (int i = r + 1; i <= n; ++i) {
            cmax(max, dp[l][r] + cnt); sum += a[i];
            while (l > 1 && sum >= a[l]) sum -= a[l --], cmax(max, dp[l][r] + cnt);
            if (!sum) ++ cnt; dp[r + 1][i] = max;
            cmax(ans, max);
        }
    }
    return printf("%d\n", ans), 0;
}