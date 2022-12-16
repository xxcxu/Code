#include <bits/stdc++.h>
#define int long long
#define eb emplace_back
using pii = std::pair<int, int>;
static constexpr int N = 778, M = 7778;
void cmin(int &x, int y) {if (y < x) x = y;}
void cmax(int &x, int y) {if (y > x) x = y;}
int n, m, tot, dis[M][M], id[N][N], ans[N][N];
char map[N][N];
std::vector<pii> e[M];
void calc(int x) {
    std::memset(dis, 10, sizeof dis);
    std::memset(dis[x], 0, sizeof dis[x]);
    for (int d = tot + 2; d >= 2; --d)
        for (int i = 1; i <= tot; ++i)
            for (auto [to, co] : e[i])
                cmin(dis[to][d - 1], dis[i][d] + (d - 1) * co);
}
signed main() {
    freopen("U.in", "r", stdin);
    freopen("U.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    int sx, sy;
    for (int i = 1; i <= n; ++i) scanf("%s", map[i] + 1);
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= m; ++j) 
            if (map[i][j] == 'G') sx = i, sy = j;
    map[sx][sy] = '#';
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (map[i][j] == '#') id[i][j] = ++ tot; 
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (map[i][j] == '#') {
                for (int k = i + 1; k <= n; ++k) if (map[k][j] == '#') {e[id[i][j]].eb(id[k][j], k - i); break;}
                for (int k = i - 1; k >= 1; --k) if (map[k][j] == '#') {e[id[i][j]].eb(id[k][j], i - k); break;}
                for (int k = j + 1; k <= m; ++k) if (map[i][k] == '#') {e[id[i][j]].eb(id[i][k], k - j); break;}
                for (int k = j - 1; k >= 1; --k) if (map[i][k] == '#') {e[id[i][j]].eb(id[i][k], j - k); break;}
            }
    calc(id[sx][sy]);
    std::memset(ans, 10, sizeof ans);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (map[i][j] == '#') {
                ans[i][j] = dis[id[i][j]][1];
                for (int k = i + 1; k <= n; ++k) if (map[k][j] == '#') break; else cmin(ans[k][j], dis[id[i][j]][2] + k - i);
                for (int k = i - 1; k >= 1; --k) if (map[k][j] == '#') break; else cmin(ans[k][j], dis[id[i][j]][2] + i - k);
                for (int k = j + 1; k <= m; ++k) if (map[i][k] == '#') break; else cmin(ans[i][k], dis[id[i][j]][2] + k - j);
                for (int k = j - 1; k >= 1; --k) if (map[i][k] == '#') break; else cmin(ans[i][k], dis[id[i][j]][2] + j - k);
            }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            printf("%lld%c", ans[i][j] == ans[0][0] ? -1 : ans[i][j], " \n"[j == m]);
    return 0;
}