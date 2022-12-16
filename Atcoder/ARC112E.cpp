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
static constexpr int N = 3e3 + 5, P = 998244353;
int n, m, ans;
int a[N], pdw[N], inv[N], fac[N];
int dp[N][N];
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
void init(int n) {
    fac[0] = pdw[0] = 1;
    for (int i = 1; i <= n; ++i) pdw[i] = pdw[i - 1] * 2ll % P;
    for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
    inv[n] = qpow(fac[n], P - 2, P);
    for (int i = n - 1; ~i; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % P;
}
int C(int n, int m) {
    if (n < m) return 0;
    return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}
signed main() {
    read(n, m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    init(m); dp[0][0] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = (dp[i - 1][j - 1] + 2ll * j % P * dp[i - 1][j] % P) % P;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            int valid = n + i - j - 1, left = i - 1;
            ans = (ans + 1ll * C(valid, left) * dp[m][valid] % P) % P;
            if (a[j] > a[j + 1]) break;
        }
    }
    for (int i = 0; i <= n; ++i) ans = (ans + 1ll * dp[m][n] * C(n, i) % P) % P;
    printf("%d\n", ans);
    return 0;
}