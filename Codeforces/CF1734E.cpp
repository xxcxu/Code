#include <bits/stdc++.h>

static constexpr int N = 350 + 5;

int n, b[N], a[N][N];

signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", b + i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) a[i][j] = i * j % n;
    for (int i = 1; i <= n; ++i) {
        int add = b[i] - a[i][i];
        for (int j = 1; j <= n; ++j) {
            a[i][j] += add;
            a[i][j] = (a[i][j] + n) % n;
            printf("%d ", a[i][j]);
        } puts("");
    } return 0; 
}+