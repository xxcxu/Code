#include <bits/stdc++.h>
static const int N = 105, M = 1005, P = 1000000007;
int n, L, a[N];
int f[2][N][M][3];
void cinc(int &x, int y) {x = (x + y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}
signed main() {
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    std::stable_sort(a + 1, a + n + 1);
    if (n == 1) return puts("1"), 0;
    int now = 0, nxt = 1;
    f[0][0][0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i + 1; ++j)
            for (int k = 0; k <= L; ++k)
                for (int l = 0; l <= 2; ++l) f[nxt][j][k][l] = 0; 
        for (int j = 0; j <= i + 1; ++j)
            for (int k = 0; k <= L; ++k)
                for (int l = 0; l <= 2; ++l) {
                    int nk = (2 * j - l) * (a[i + 1] - a[i]) + k;
                    if (nk < 0 || nk > L) continue;
                    if (j <= i) cinc(f[nxt][j + 1][nk][l], mul(f[now][j][k][l], j + 1 - l));
                    if (l <  2) cinc(f[nxt][j + 1][nk][l + 1], mul(f[now][j][k][l], 2 - l));
                    if (j + j > l) cinc(f[nxt][j][nk][l], mul(f[now][j][k][l], 2 * j - l));
                    if (j >= 1) cinc(f[nxt][j - 1][nk][l], mul(f[now][j][k][l], j - 1));
                    if (l <  2) cinc(f[nxt][j][nk][l + 1], mul(f[now][j][k][l], 2 - l));
                }
        now ^= 1;
        nxt ^= 1;
    }
    int ans = 0;
    for (int i = 0; i <= L; ++i) cinc(ans, f[now][1][i][2]);
    return printf("%d", ans), 0;
}