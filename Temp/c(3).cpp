#include <bits/stdc++.h>
#define eb emplace_back
#define all(x) x.begin(), x.end()
static constexpr int N = 2e5 + 5;
int n, w[N], ans[N], vis[N];
std::vector<int> e[N];
void dfs(int x) {
    vis[x] = true;
    for (int y : e[x]) if (!vis[y]) dfs(y);
}
signed main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", w + i);
    for (int i = 2; i <= n; ++i) e[i / 2].eb(i);
    for (int i = 1; i < (1 << n); ++i) {
        static std::vector<int> v1, v2;
        v1.clear(); v2.clear();
        for (int j = 1; j <= n; ++j) if (i >> (j - 1) & 1) v1.emplace_back(j);
        for (int j = 1; j <= n; ++j) if (i >> (j - 1) & 1) v2.emplace_back(w[j]);
        int k = (int)v1.size();
        std::sort(all(v2));
        for (int j = 1; j <= n; ++j) vis[j] = true;
        for (int j : v1) vis[j] = false;
        dfs(v1[0]);
        bool flag = true;
        for (int j : v1) flag &= vis[j] == true;
        if (flag)
            for (int j = 0; j < k; ++j) ans[j] = std::max(ans[j], v2[(k - j + 1) / 2 - 1]); 
    }
    for (int i = 0; i < n; ++i) printf("%d ", ans[i]); puts("");
    return 0;
}