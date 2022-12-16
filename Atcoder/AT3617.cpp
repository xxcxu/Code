#include <bits/stdc++.h>
const int N = 3e2 + 5, mod = 1e9 + 7;
int n, ans, deg[N], fac[N], inv[N], finv[N], f[N][N][2];
int Add(int x, int y) {return (x + y) % mod;}
void cAdd(int &x, int y) {x = Add(x, y);}
int Mul(int x, int y) {return 1ll * x * y % mod;}
void cMul(int &x, int y) {x = Mul(x, y);}
void Init(int n) {
    fac[0] = fac[1] = inv[1] = finv[0] = finv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fac[i] = Mul(fac[i - 1], i);
        inv[i] = Mul((mod - mod / i), inv[mod % i]);
        finv[i] = Mul(finv[i - 1], inv[i]);
    } return void();
}
signed main() {
    scanf("%d", &n); Init(n); bool circle = true;
    for (int i = 1; i <= n; ++i) scanf("%d", deg + i);
    for (int i = 1; i <= n; ++i) circle &= deg[i] == 2;
    if (circle) return printf("%d\n", Mul(fac[n - 1], inv[2])), 0;
    f[0][0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= i; ++j)
            for (int k = 0; k < 2; ++k) {
                if (deg[i] >= 1) cAdd(f[i][j][k], Mul(f[i - 1][j][k], finv[deg[i] - 1])); // normal point
                if (deg[i] >= 2) cAdd(f[i][j][k], Mul(f[i - 1][j - 1][k], finv[deg[i] - 2])); // circle point
                if (deg[i] >= 3 && k) cAdd(f[i][j][k], Mul(f[i - 1][j - 1][k - 1], finv[deg[i] - 3])); // special point
            }
    for (int i = 3; i <= n; ++i) cAdd(ans, Mul(f[n][i][1], Mul(fac[n - i - 1], Mul(fac[i - 1], inv[2]))));
    return printf("%d\n", ans), 0;
}