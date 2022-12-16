#include <bits/stdc++.h>
static constexpr int N = 5e6 + 5;
int P, n, m, ans, fac[N], inv[N];
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return mul(fac[n], mul(inv[m], inv[n - m]));
}
int f(int k) {
    int t = n * m - k * (m + 1);
    return mul(C(n * 2, k), C(n * 2 + t - 1, t));
}
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x)) if (y & 1) ans = mul(ans, x);
    return ans % P;
}
void solve() {
    scanf( "%d%d", &n, &m); ans = 0;
    for (int i = 0; i <= n; ++i)
        if (i & 1) ans = dec(ans, f(i));
        else ans = inc(ans, f(i));
    ans = mul(ans, qpow(qpow(m + 1, 2 * n, P), P - 2, P));
    printf("%d\n", mul(dec(1, ans), qpow(2, P - 2, P)));
}
signed main() {
    freopen("Y.in", "r", stdin);
    freopen("Y.out", "w", stdout);
    int t; scanf("%d%d", &P, &t);
    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = mul(fac[i - 1], i);
    inv[N - 1] = qpow(fac[N - 1], P - 2, P);
    for (int i = N - 2; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    while (t--) solve();
    return 0;
}  