#include <bits/stdc++.h>
static constexpr int N = 5e3 + 5, P = 998244353;
auto Inc(int x, int y) -> int {return (x + y >= P) ? x + y - P : x + y;}
auto cInc(int &x, int y) -> void {x = Inc(x, y);}
auto Mul(int x, int y) -> int {return 1ll * x * y % P;}
auto cMul(int &x, int y) -> void {x = Mul(x, y);}
int n, m, a[N], f[N][N];
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    std::stable_sort(a + 1, a + n + 1);
    f[1][0] = 1;
    for (int i = 1, k = 1; i < n; ++i, ++k) {
        if (a[i] != a[i + 1]) k = 0;
        for (int j = 0; j <= m; ++j) {
            cInc(f[i + 1][j], Mul(j + k + 1, f[i][j]));
            if (i - j - k > 0)
                cInc(f[i + 1][j + 1], Mul(i - j - k, f[i][j]));
        }
    } return printf("%d\n", f[n][m]), 0;
}