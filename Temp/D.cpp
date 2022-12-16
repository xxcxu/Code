#include <bits/stdc++.h>
static constexpr int N = 2e6 + 5, M = 1e3 + 5;
int n, m, a[N], cnt[N];
int ans[M][M];
std::vector<int> num[N];
// signed main() {
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) {
        int l = i, r = i;
        for (int j = i; j <= n; ++j) {
            ++ cnt[a[j]];
            if (cnt[a[j]] == 1) r = j - 1;
            ans[i][j] = r - l + 1;
        }
        for (int j = i; j <= n; ++j) -- cnt[a[j]];
    }
    while (m --) {
        static int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", ans[l][r]);
    }
}