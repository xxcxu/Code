#include <bits/stdc++.h>
const int N = 1e5 + 5;
int t, n, f[N][2];
std::vector<int> Graph[N];
void Dfs(int x, int fa) {
    int cnt = 0; f[x][0] = f[x][1] = 1;
    for (auto y : Graph[x]) {
        if (y == fa) continue; Dfs(y, x);
        f[x][0] = std::min(f[x][0] + f[y][0], f[x][1] + f[y][1] - 1);
        f[x][1] = std::min(f[x][1] + f[y][0], cnt + f[y][1]);
        cnt += f[y][0];
    } return void();
}
signed main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) Graph[i].clear();
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            Graph[u].emplace_back(v);
            Graph[v].emplace_back(u);
        } Dfs(1, 0);
        printf("%d\n", std::min(f[1][0], f[1][1]));  
    } return 0;
}