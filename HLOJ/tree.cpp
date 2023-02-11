#include <bits/stdc++.h>
#define eb emplace_back
static const int N = 500005, M = 55;
int n, ans;
int a[N], size[N][2];
std::vector<int> e[N];
void dfs(int x, int fa) {
    size[x][a[x]] = 1;
    for (int y : e[x]) if (y != fa) {
        dfs(y, x);
        size[x][0] += size[y][0];
        size[x][1] += size[y][1];
        ans += std::abs(size[y][1] - size[y][0]);
    }
}
signed main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) a[i] = a[i] & 1 ? 1 : 0;
    for (int i = 1; i < n; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        e[u].eb(v); e[v].eb(u);
    }
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}