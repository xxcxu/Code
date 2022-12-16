#include <bits/stdc++.h>
using uint = u_int32_t;
static constexpr int N = 1e6 + 5, P = 998244353;
int a, b;
int f[N];
int inc(int x, int y); int dec(int x, int y);
int mul(int x, int y); int qpow(int x, int y, int P);
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x)) if (y & 1) ans = mul(ans, x);
    return ans % P;
}
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
signed main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%d%d", &a, &b);
    f[1] = 1;
    for (uint i(1); i <= a; ++i) {
        f[0] = f[1];
        f[1] = inc(f[0], qpow(i * 2 + 1, P - 2, P));
    }
    for (uint i(2); i <= b; ++i) f[i] = inc(f[i - 1], qpow(a * 2 + i, P - 2, P));
    printf("%d\n", f[b]);
    return 0;
}