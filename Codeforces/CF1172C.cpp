#include <bits/stdc++.h>
static constexpr int N = 2e5 + 5, M = 3e3 + 5, P = 998244353;
int n, m, A, B, S;
int a[N], w[N], f[M][M], g[M][M];
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i); 
    for (int i = 1; i <= n; ++i) scanf("%d", w + i);
    for (int i = 1; i <= n; ++i) if (a[i]) A += w[i];
    for (int i = 1; i <= n; ++i) if (!a[i]) B += w[i];
    S = A + B;
    for (int i = m; ~i; --i) {
        f[i][m - i] = g[i][m - i] = 1;
        for (int j = std::min(m - i - 1, B); j >= 0; --j) {
            f[i][j] = (1ll * (A + i + 1) * f[i + 1][j] % P + 1ll * (B - j) * f[i][j + 1] % P) % P * qpow(i - j + S, P - 2, ·P) % P;
            g[i][j] = (1ll * (A + i) * g[i + 1][j] % P + 1ll * (B - j - 1) * g[i][j + 1] % P) % P * qpow(i - j + S, P - 2, P) % P;
        }
    }
    for (int i = 1; i <= n; ++i) w[i] = 1ll * w[i] * (a[i] ? f[0][0] : g[0][0]) % P;
    for (int i = 1; i <= n; ++i) printf("%d\n", w[i]);
    return 0;
}
