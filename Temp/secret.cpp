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
static constexpr int N = 20, P = 65535;
int n, m, p[N], fac[N];
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
void solve() {
    read(n); 
    fac[0] = 1; m = 0;
    int ans = 1, mul = 1;
    for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P; 
    for (int i = 1; i <= n; ++i) {
        static int x, y;
        read(x, y);
        mul = 1ll * mul * fac[y] % P;
        while (y--) p[++ m] = x + 1;
    }
    do {
        int prod = 0, base = 1;
        for (int i = 1; i <= m; ++i) {
            prod = (prod + 1ll * (p[i] - 1) * base % P) % P;
            base = 1ll * base * 256 % P;    
        } 
        ans = 1ll * ans * prod % P;
    } while (std::next_permutation(p + 1, p + m + 1));
    printf("%d\n", qpow(ans, mul, P));
}
signed main() {
    freopen("secret.in", "r", stdin);
    freopen("secret.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
}