#include <bits/stdc++.h>
static constexpr int N = 5e3 + 5, P = 1e9 + 7;
int n, a[N], f[N][N];
char str[N];
int add(int x, int y) {return (x + y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
signed main() {
    freopen("stri.in", "r", stdin);
    freopen("stri.out", "w", stdout);
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for (int i = 1; i <= n; ++i) a[i] = (str[i] == '+');
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0 + a[i]; j <= i; ++j)
            if (a[i]) f[i][j] = add(f[i - 1][j - 1], mul(f[i - 1][j], j));
            else f[i][j] = add(mul(f[i - 1][j], j), mul(f[i - 1][j + 1], mul(j + 1, j + 1)));
    printf("%d\n", f[n][0]);     
    return 0;
}