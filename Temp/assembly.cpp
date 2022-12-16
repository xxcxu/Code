#include <bits/stdc++.h>
using ll = long long;
static constexpr int N = 25e4 + 5, M = 5e3 + 5;
int n, dis[M][M];
struct node {int r, c;} a[N];
std::vector<int> e[N];
void bfs(int sx) {
    std::memset(dis[sx], -1, sizeof dis[sx]);
    std::queue<int> q; dis[sx][sx] = 0; q.emplace(sx);
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int y : e[x]) 
            if (!~dis[sx][y]) 
                dis[sx][y] = dis[sx][x] + 1, q.emplace(y); 
    }
}
signed main() {
    freopen("assembly.in", "r", stdin);
    freopen("assembly.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].r, &a[i].c);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (i != j)
                if (a[i].r > a[j].r && a[i].c > a[j].c)
                    e[i].emplace_back(j), e[j].emplace_back(i);
    for (int i = 1; i <= n; ++i) bfs(i);
    for (int i = 1; i <= n; ++i) {
        ll sum = 0;
        for (int j = 1; j <= n; ++j) sum += dis[i][j];
        printf("%lld\n", sum);
    }
    return 0;
}