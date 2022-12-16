#include <bits/stdc++.h>
using ll = long long;
static constexpr int N = 5e5 + 5, P = 1e9 + 7;
int n, a[N], dp[N], s[N]; ll sum[N];
std::unordered_map<ll, int> map;
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
signed main() {
    freopen("segment.in", "r", stdin);
    freopen("segment.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
    dp[0] = 1; s[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int p = map[sum[i]];
        dp[i] = p ? dec(s[i - 1], s[p - 1]) : s[i - 1];
        s[i] = inc(s[i - 1], dp[i]);
        map[sum[i]] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = inc(ans, dp[i - 1]);
    printf("%d\n", ans);
    return 0;
}