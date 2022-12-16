#include <bits/stdc++.h>
static constexpr int N = 1e7 + 5;
int p, a, d, n;
int fac[2 * N];
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
int inc(int x, int y) {return (x + y) % p;}
int dec(int x, int y) {return (x + p - y) % p;}
int mul(int x, int y) {return 1ll * x * y % p;}
int divi(int x, int y) {return 1ll * x * qpow(y, p - 2, p) % p;}
void solve() {
    scanf("%d%d%d", &a, &d, &n);
    if (!d) return printf("%d\n", qpow(a, n, p)), void();
    if (n >= p) return printf("%d\n", 0), void();
    int offset = mul(a, qpow(d, p - 2, p));
    return printf("%d\n", mul(qpow(d, n, p), divi(fac[offset + n - 1], fac[offset - 1]))), void();
}
signed main() {
    freopen("story.in", "r", stdin);
    freopen("story.out", "w", stdout);
    int t; scanf("%d%d", &t, &p);
    fac[0] = 1;
    for (int i = 1; i <= 2 * p; ++i) fac[i] = mul(fac[i - 1], i);
    while (t--) solve();
    return 0;
}