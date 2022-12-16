#include <bits/stdc++.h>
static constexpr int N = 1e6 + 5, P = 998244353;
int n, k, a[N], su[N], power10[N];
char s[N];
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
int sum(std::vector<int> v) {
    int ans = 0;
    for (int u : v) ans = inc(ans, u);
    return ans;
}
int calc(int l, int r) {return dec(su[r], mul(su[l - 1], power10[r - l + 1]));}
signed main() {
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
    scanf("%d%d%s", &n, &k, s + 1); power10[0] = 1;
    for (int i = 1; i <= n; ++i) a[i] = s[i] - '0';
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
    for (int i = 1; i <= n; ++i) power10[i] = mul(power10[i - 1], 10);
    for (int i = 1; i <= n; ++i) su[i] = inc(mul(su[i - 1], 10), a[i]);
    for (int i = 1; i <= n; ++i) dp[i][1] = calc(1, i);
    for (int i = 1; i <= n; ++i)
        for (int j = 2; j <= k; ++j)
            for (int k = 1; k < i; ++k)
                dp[i][j] = inc(dp[i][j], inc(dp[k][j - 1], calc(k + 1, i)));
    printf("%d\n", sum(dp[n]));
    return 0;
}