#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e3 + 5, inf = 1e9 + 7;
int n, m, t, a[N], s[N], dp[N], f[N];
int min(int *dp) {
    int mi = inf;
    for (int i = m; i <= n; ++i) mi = std::min(mi, dp[i]);
    return mi;
}
int getx(int x) {return x;}
int gety(int x) {return f[x];}
double slope(int x, int y) {return 1.0 * (gety(x) - gety(y)) / (getx(x) - getx(y));}
void solve() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    std::sort(a + 1, a + n + 1, [&](int x, int y) {return x > y;});
    for (int i = 1; i <= n; ++i) f[i] = inf;
    for (int i = 1; i <= m; ++i) {
        s[t = 1] = i - 1;
        for (int j = i; j <= n; ++j) {
            while (t > 1 && slope(s[t], s[t - 1]) > a[j]) -- t;
            dp[j] = f[s[t]] - s[t] * a[j] + j * a[j];
            while (t > 1 && slope(s[t], j) < slope(s[t], s[t - 1])) -- t;
            s[++ t] = j;
        }
        for (int j = 1; j <= n; ++j) f[j] = dp[j];
    }
    printf("%lld\n", min(f));
}
signed main() {
    freopen("contest.in", "r", stdin);
    freopen("contest.out", "w", stdout);
    int t; scanf("%lld", &t);
    while (t--) solve();
    return 0;
}