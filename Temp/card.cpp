#include <bits/stdc++.h>
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
static constexpr int N = 35, P = 1e9 + 7;
int a, b, n;
int fac[N], inv[N];
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
    inv[n] = qpow(fac[n], P - 2, P);
    for (int i = n - 1; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % P;
}
signed main() {
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    read(a, b, n); init(a + b); 
    if (b < n) return puts("1"), 0;
    int res = 1ll * fac[a + b - n] % P * inv[b - n] % P * inv[a] % P;
    int all = 1ll * fac[a + b] * inv[a] % P * inv[b] % P;
    printf("%lld\n", 1ll * (all + P - res) % P * qpow(all, P - 2, P) % P);
    return 0;
}