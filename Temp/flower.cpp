#include <bits/stdc++.h>
static constexpr int M = 20, N = 25, inf = 1e9 + 7;
int n, a[N], cnt[N], dp[1 << M];
void cmin(int &x, int y) {if (y < x) x = y;}
void cmax(int &x, int y) {if (y > x) x = y;}
int count(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ++ ans;
    return ans;
}
void solve() {
    scanf("%d", &n);
    for (int i = 1; i < N; ++i) cnt[i] = 0;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) ++ cnt[a[i]];
    if (cnt[1] > 1) return puts("Poor hzwer!"), void();
    for (int mask = 0; mask < 1 << n; ++mask) {
        dp[mask] = inf;
        if (count(mask) == 1) dp[mask] = 1;
        else {
            for (int i = 1; i <= n; ++i)
                if (mask >> (i - 1) & 1) {
                    int S = mask ^ (1 << i - 1);
                    if (a[i] != 1) cmin(dp[mask], dp[S] + (int)std::ceil(1.0 * dp[S] / (a[i] - 1))); 
                }
        }
    }
    printf("%d\n", dp[(1 << n) - 1]);
}
signed main() {
    freopen("flower.in", "r", stdin);
    freopen("flower.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
}