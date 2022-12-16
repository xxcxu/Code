#include <bits/stdc++.h>
static constexpr int N = 1e6 + 5, P = 998244353;
int n, k, ans, sum;
int fac[N], finv[N], pow10[N], f[N], g[N];
char s[N];
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
int inv(int x) {return qpow(x, P - 2, P);}
int C(int n, int m) {if (n < 0 || m < 0 || n < m) return 0; return mul(fac[n], mul(finv[m], finv[n - m]));}
void init(int n) {
    fac[0] = pow10[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    for (int i = 1; i <= n; ++i) pow10[i] = mul(pow10[i - 1], 10);
    finv[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; --i) finv[i] = mul(finv[i + 1], i + 1);
}
void solve() {
    scanf("%d%d%s", &n, &k, s + 1); ans = sum = 0;
    for (int i = 1; i <= n; ++i) s[i] -= '0';
    f[0] = 1; g[0] = k > 1;
    for (int i = 1; i <= n; ++i) f[i] = dec(mul(f[i - 1], 2), C(i - 1, k - 1));
    for (int i = 1; i <= n; ++i) g[i] = dec(mul(g[i - 1], 2), C(i - 1, k - 2));
    for (int i = 1; i <= n; ++i) ans = inc(ans, mul(s[i], mul(pow10[n - i], f[i - 1])));
    for (int i = n - 1; i >= 1; --i) {
        sum = inc(sum, mul(pow10[n - i - 1], g[i - 1]));
        ans = inc(ans, mul(s[i], sum));
    }
    printf("%d\n", ans);
}
signed main() {
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
    init(N - 1);
    int t; t = 1;  
    while (t--) solve();
}