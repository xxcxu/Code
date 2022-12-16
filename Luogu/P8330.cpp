#include <bits/stdc++.h>
static constexpr int N = 2e5 + 3, T = 449, inf = 0x3f3f3f3f;
int n, m, a[N], b[N], ans[N], pre[N], cnt[N], g[N][T];
std::vector<int> c[N];
auto Solve1(int x) -> void {
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + (a[i] == x);
    for (int i = 1; i <= m; ++i) if (i ^ x) {
        int max = -1, min = 0, id = 0;
        for (int j : c[i]) {
            -- id;
            ans[x] = std::max(ans[x], max - pre[j] - id + 1);
            ans[i] = std::max(ans[i], pre[j] + id - min + 1);
            max = std::max(max, pre[j] + id);
            min = std::min(min, pre[j] + id);
        }
        ans[x] = std::max(ans[x], max - pre[n] - id + 1);
        -- id;
        ans[i] = std::max(ans[i], pre[n] + id - min + 1);
    }
}
auto Solve2(int x) -> void {
    int size = c[x].size();
    for (int i = 0; i < size; ++i)
        for (int j = i; j < size; ++j)
            g[c[x][i]][j - i + 1] = std::min(c[x][j], g[c[x][i]][j - i + 1]);
}
auto main() -> decltype(0) {
    int Case; scanf("%d", &Case);
    for (; Case--;) {
        scanf("%d", &n);
        for (int i = 1;  i <= n; ++i) scanf("%d", a + i), b[i] = a[i];
        std::stable_sort(b + 1, b + n + 1);
        m = std::unique(b + 1, b + n + 1) - b - 1;
        for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(b + 1, b + m + 1, a[i]) - b;
        for (int i = 1; i <= m; ++i) c[i].clear(), ans[i] = 0;
        for (int i = 1; i <= n; ++i) c[a[i]].emplace_back(i);
        for (int i = 1; i <= m; ++i) if (c[i].size() >= T) Solve1(i);
        for (int i = 1; i <= n + 1; ++i)
            for (int j = 1; j < T; ++j) g[i][j] = inf;
        for (int i = 1; i <= m; ++i) if (c[i].size() < T) Solve2(i);
        for (int i = n; i; --i)
            for (int j = 1; j < T; ++j)
                g[i][j] = std::min(g[i][j], g[i + 1][ j]);
        for (int i = 1; i <= m; ++i) if (c[i].size() < T) {
            int size = c[i].size();
            for (int j = 1, k = 0; j < T && g[1][j] != inf; ++j) {
                while (k < size && g[1][j] >= c[i][k]) ++ k;
                ans[i] = std::max(ans[i], j - k);
            }
            for (int j = 0; j < size; ++j)
                for (int k = c[i][j] + 1, l = 1, o = j + 1; l < T && g[k][l] != inf; ++l) {
                    while (o < size && g[k][l] >= c[i][o]) ++ o;
                    ans[i] = std::max(ans[i], l - o + j + 1);
                }
        }
        for (int i = 1; i <= m; ++i) ans[i] += (int)(c[i].size());
        int max = 0;
        for (int i = 1; i <= m; ++i) if (ans[i] > max) max = ans[i];
        printf("%d\n", max);
        for (int i = 1; i <= m; ++i) if (ans[i] == max) printf("%d\n", b[i]);
	} return 0;
}