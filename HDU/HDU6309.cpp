#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5, P = 998244353;
int n, m, ans, l[N], r[N];
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
void dfs(int x, int sum, int f1, int f2) {
    if (x == n + 1) {
        if (sum > 0) ans = inc(ans, mul(f1, qpow(sum, n + 1, P)));
        if (sum < 0) ans = dec(ans, mul(f2, qpow(P - sum, n + 1, P)));
        return void();
    }
    dfs(x + 1, sum + l[x], P - f1, f2);
    dfs(x + 1, sum + r[x], f1, P - f2);
}
signed main() {
    scanf("%d", &n); m = n + 1;
    for (int i = 1; i <= n; ++i) scanf("%d%d", l + i, r + i);
    for (int i = 1; i <= n; ++i) m = mul(m, mul(r[i] - l[i], i));
    dfs(1, 0, 1, P - 1);
    printf("%d\n", mul(ans, qpow(m, P - 2, P)));
}