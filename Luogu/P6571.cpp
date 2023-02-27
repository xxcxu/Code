#include <bits/stdc++.h>
using pii = std::pair<int, int>;
#define eb emplace_back
static const int N = 50005;
int n, k, time_stamp, d[N], uni[N], dfn[N];
std::vector<int> e[N], g[N];
std::map<pii, int> edge;
bool vis[N];
void dfs(int x) {
    vis[x] = true;
    dfn[x] = ++ time_stamp;
    for (int y : e[x]) {
        -- d[y];
        if (d[y] < k && !vis[y]) dfs(y);
    }
}
bool beside(int x, int y) {
    return edge[pii(x, y)] || edge[pii(y, x)];
    // for (int a : g[x]) if (a == y) return true;
    // for (int b : g[y]) if (b == x) return true;
    // return false;
}
int calc(int x) {
    int s = (int)g[x].size();
    for (int i = 0; i < s; ++i) uni[i] = 0;
    for (int i = 0; i < s; ++i) {
        uni[i] |= 1 << i;
        for (int j = 0; j < s; ++j) 
            uni[i] |= beside(g[x][i], g[x][j]) << j;
    }
    int ans = 0;
    for (int i = 0; i < (1 << s); ++i) {
        int res = i, cnt = 0;
        for (int j = 0; j < s; ++j)
            if (i >> j & 1) res &= uni[j], ++ cnt;  
        if (res == i) ans = std::max(ans, cnt);
    }
    return ans + 1;
}
signed main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", d + i);
        for (int j = 1, x; j <= d[i]; ++j) 
            scanf("%d", &x), ++ x, e[i].eb(x);
    }
    for (int i = 1; i <= n; ++i) if (d[i] < k && !vis[i]) dfs(i);
    for (int i = 1; i <= n; ++i)
        for (int j : e[i]) if (dfn[i] < dfn[j]) g[i].eb(j), edge[pii(i, j)] = true;
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = std::max(ans, calc(i));
    return printf("%d\n", ans), 0;
}