#pragma GCC optimize("fast")
#include <bits/stdc++.h>
static constexpr int N = 2e5 + 5;
int n, q;
int x[N], y[N];
signed main() {
    freopen("pair.in", "r", stdin);
    freopen("pair.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", x + i, y + i);
    scanf("%d", &q);
    while (q--) {
        static int t;
        scanf("%d", &t);
        int ans = 0;
        for (int i = 1; i <= n; ++i) ans = std::max(ans, (t + x[i]) xor y[i]);
        printf("%d\n", ans);
    } return 0;
}