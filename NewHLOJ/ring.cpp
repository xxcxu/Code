#include <bits/stdc++.h>
static const int N = 3000005, P = 1000000007;
int r, g, b, p, q, fac[N], inv[N];
int inc(int x, int y) {return (x + y)     % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x)) if (y & 1) ans = mul(ans, x);
    return ans % P;
}
int binom(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return mul(fac[n], mul(inv[m], inv[n - m]));
}
void sieve(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2, P);
    for (int i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    return void();
}
void solve() {
    scanf("%d%d%d%d%d", &r, &g, &b, &p, &q);
    int res = mul(fac[g - 1], mul(fac[r], fac[b]));
    if (g == 0) {
        int ans = fac[r + b - 1];
        printf("%d\n", ans);
        return void();
    }
    if (r == 0) {
        int ans = mul(binom(b - g * q + g - 1, g - 1), res);
        printf("%d\n", ans);
        return void();
    }
    if (b == 0) {
        int ans = mul(binom(g - r * p + r - 1, r - 1), mul(fac[r - 1], fac[g]));
        if (q) ans = 0;
        printf("%d\n", ans);
        // return void();
    }
    if (p == 0) {
        int ans = mul(mul(binom(b - g * q + g - 1, g - 1), binom(r + g + b - 1, g + b - 1)), res);
        printf("%d\n", ans);
        return void();
    }
    if (q == 0) {
        int ans = mul(mul(binom(g - r * p + r - 1, r - 1), binom(r + g + b - 1, r + g - 1)), mul(fac[r - 1], mul(fac[g], fac[b])));
        printf("%d\n", ans);
        return void();
    }
    {
        int ans = 0;
        for (int i = 0; i <= r; ++i) ans = inc(ans, mul(binom(b - g * q + g + i - 1, g + i - 1), mul(qpow(q, r - i, P), binom(r, i))));
        ans = mul(mul(ans, binom(g - r * p + r - 1, r - 1)), mul(fac[r - 1], mul(fac[g], fac[b])));
        printf("%d\n", ans);
        return void();
    }
}
signed main() {
    freopen("ring.in", "r", stdin);
    freopen("ring.out", "w", stdout);
    sieve(N - 1);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}