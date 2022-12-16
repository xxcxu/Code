#include <bits/stdc++.h>
static constexpr int N = 2e5 + 5, M = 1e6 + 5;
int n, cnt, ans, a[N], b[M], c[M];
signed main() {
    freopen("odd.in", "r", stdin);
    freopen("odd.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int l = 1; l <= n; ++l) {
        cnt = 0;
        for (int r = l; r <= n; ++r) {
            b[a[r]] ^= 1;
            if (c[a[r]]) cnt += b[a[r]] ? -1 : 1;
            c[a[r]] = 1;
            if (!cnt) ++ ans;
        }
        for (int r = l; r <= n; ++r) b[a[r]] ^= 1, c[a[r]] = 0;
    }
    return printf("%d\n", ans), 0;
}