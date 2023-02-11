#include <bits/stdc++.h>
static const int N = 75;
struct Node {int x, val, pin;} a[N];
int n, m, k, b[N], sum[N], f[N][N][N];
void cmin(int &x, int y) {if (y < x) x = y;}
void cmax(int &x, int y) {if (y > x) x = y;}
signed main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i].x);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i].val);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i].pin);
    for (int i = 1; i <= n; ++i) b[i] = a[i].val;
    std::sort(b + 1, b + n + 1);
    m = std::unique(b + 1, b + n + 1) - b - 1;
    std::sort(a + 1, a + n + 1, [&](Node &a, Node &b) {return a.x < b.x;});
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i].pin;
    for (int i = 1; i <= n; ++i) a[i].val = std::lower_bound(b + 1, b + m + 1, a[i].val) - b;
    std::memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n + 1; ++i)
        for (int j = 1; j <= n; ++j) f[i][i - 1][j] = 0;
    for (int i = n; i >= 1; --i)
        for (int j = i; j <= n; ++j)    
            for (int K = 1; K <= n; ++K)
                for (int l = i; l <= j; ++l) {
                    if (a[l].val >= K) cmin(f[i][j][K], f[i][l - 1][a[l].val] + f[l + 1][j][a[l].val] + sum[j] - sum[i - 1]);
                    cmin(f[i][j][K], f[i][l - 1][K] + f[l + 1][j][K] + k + sum[j] - sum[i - 1]); 
                }
    return printf("%d\n", f[1][n][1]), 0;
}