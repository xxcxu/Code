#include <bits/stdc++.h>
using pii = std::pair<int, int>;
#define fi first
#define se second
static constexpr int N = 2e3 + 5;
static constexpr pii dir[] = {pii(1, 0), pii(-1, 0), pii(0, 1), pii(0, -1)};
int n, m;
int ds[N][N];
char map[N][N];
std::stack<pii> q;
auto Topsort() -> void {
    while (q.size()) {
        pii t = q.top(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int x = t.fi + dir[d].fi;
            int y = t.se + dir[d].se;
            if (map[x][y] == '.') {
                switch(d) {
                    case 0: map[t.fi][t.se] = '^', map[x][y] = 'v'; break;
                    case 1: map[t.fi][t.se] = 'v', map[x][y] = '^'; break;
                    case 2: map[t.fi][t.se] = '<', map[x][y] = '>'; break;
                    case 3: map[t.fi][t.se] = '>', map[x][y] = '<'; break;
                    default: break;
                }
                for (int di = 0; di < 4; ++di) {
                    int x1 = x    + dir[di].fi, y1 = y    + dir[di].se;
                    int x2 = t.fi + dir[di].fi, y2 = t.se + dir[di].se;    
                    if (map[x1][y1] == '.' and (-- ds[x1][y1]) == 1) q.emplace(x1, y1);
                    if (map[x2][y2] == '.' and (-- ds[x2][y2]) == 1) q.emplace(x2, y2);
                }
                break;
            }
        }
    }
}
auto main() -> decltype(0) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%s", map[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            for (int d = 0; d < 4; ++d) 
                ds[i][j] += (map[i + dir[d].fi][j + dir[d].se] == '.');
            if (ds[i][j] == 1 && map[i][j] == '.')
                q.emplace(i, j);
        }
    Topsort();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) if (map[i][j] == '.') return puts("Not unique"), 0;
    for (int i = 1; i <= n; ++i, puts(""))
        for (int j = 1; j <= m; ++j) putchar(map[i][j]);
    return 0;
}