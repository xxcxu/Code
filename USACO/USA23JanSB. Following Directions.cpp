#include <bits/stdc++.h>
#define eb emplace_back
using pii = std::pair<int, int>;
static const int N = 1505;
int n, q, ans;
char s[N];
int map[N][N], f[N][N], in[N][N];
std::vector<pii> e[N][N];
void add(int a, int b, int c, int d) {e[a][b].eb(c, d); ++ in[c][d];}
void init() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (map[i][j] == 'R') add(i, j, i, j + 1);
            if (map[i][j] == 'D') add(i, j, i + 1, j);
        }
    }
    std::queue<pii> q;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) 
            if (!in[i][j]) q.emplace(i, j);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            f[i][j] = 1;
    while (q.size()) {
        auto [a, b] = q.front(); q.pop();
        for (auto [c, d] : e[a][b]) {
            -- in[c][d];
            f[c][d] += f[a][b];
            if (!in[c][d]) q.emplace(c, d);
        }
    }
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= n; ++j) map[i][j] = (int)s[j]; 
        scanf("%d", map[i] + n + 1);
    }
    for (int i = 1; i <= n; ++i) scanf("%d", map[n + 1] + i);
    init();
    scanf("%d", &q);
    for (int i = 1; i <= n; ++i) ans += map[i][n + 1] * f[i][n + 1];
    for (int i = 1; i <= n; ++i) ans += map[n + 1][i] * f[n + 1][i];
    printf("%d\n", ans);
    while (q--) {
        static int x, y, xx, yy;
        scanf("%d%d", &x, &y);
        xx = x, yy = y;
        while (xx != n + 1 && yy != n + 1) {
                 if (map[xx][yy] == 'R') ++ yy;
            else if (map[xx][yy] == 'D') ++ xx;
            f[xx][yy] -= f[x][y];
        }
        ans -= f[x][y] * map[xx][yy];
        xx = x, yy = y;
        map[x][y] = (map[x][y] == 'R' ? 'D' : 'R');
        while (xx != n + 1 && yy != n + 1) {
                 if (map[xx][yy] == 'R') ++ yy;
            else if (map[xx][yy] == 'D') ++ xx;
            f[xx][yy] += f[x][y];
        }
        ans += f[x][y] * map[xx][yy];
        printf("%d\n", ans);
    }
    return 0;
}
