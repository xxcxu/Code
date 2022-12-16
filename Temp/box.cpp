#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5;
int n, ans, r[N], cnt[N];
signed main() {
    freopen("box.in", "r", stdin);
    freopen("box.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", r + i), ++ cnt[r[i]];
    for (int i = 1; i <= 10000; ++i) ans = std::max(ans, cnt[i]);
    return printf("%d\n", ans), 0;
}