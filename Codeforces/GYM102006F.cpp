#include <bits/stdc++.h>

static constexpr int N = 1 << 20;
int t, n, m;
int dp[N], cnt[N];

auto Dfs(int x) {
    if (~dp[x]) return dp[x];
    dp[x] = 0x3f3f3f3f;
    for (int i = 0; i < n; ++i)
        if (!(x >> i & 1))
            dp[x] = std::min(dp[x], dp[x ^ (1 << i)] + cnt[i]);
    return dp[x];
}

auto main() -> decltype(0) {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i) {
            int sta = 0;
            for (int j = 0, x; j < n; ++j) {
                scanf("%d", &x);
                if (x & 1) sta |= 1 << j;
            }
            ++ cnt[sta];
        }
        std::fill(dp, dp + (1 << n) + 1, -1);
        dp[(1 << n) - 1] = 0;
        for (int j = 0; j < n; ++j)
            for (int i = (1 << n) - 1; ~i; --i) 
                if (i >> j & 1)
                    cnt[i ^ (1 << j)] += cnt[i];
        int now = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (now >> j & 1) continue;
                if (Dfs(now | (1 << j)) + cnt[now] == Dfs(now)) {
                    now |= 1 << j;
                    printf("%d ", j + 1);
                    break;
                }
            }
            puts("");
        }
    }
    return 0;
}