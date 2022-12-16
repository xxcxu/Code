#include <bits/stdc++.h>
using pii = std::pair<int, int>;
static constexpr int N = 5e5 + 5, M = 3e3 + 2;
const int dx[] = {1, 1};
const int dy[] = {0, 1};
int n, q, a[N], d[N];
int dep[M * M / 2], anc[M * M / 2][13];
pii idx[M * M / 2];
std::vector<int> e[M * M / 2];
int id(int x, int y) {return x * (x + 1) / 2 + y + 1; }
pii reid(int x) {return idx[x];}
void add(int x, int y) {e[x].emplace_back(y);}
void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    for (auto &y : e[x]) {
        anc[y][0] = x;
        for (int i = 1; i <= 12; ++i)
            anc[y][i] = anc[anc[y][i - 1]][i - 1];
        dfs(y, x);
    }
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = 12; ~i; --i)
        if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;   
    for (int i = 12; ~i; --i)
        if (anc[x][i] != anc[y][i])
            x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}
signed main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 0; i < n; ++i) d[i] = 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= i; ++j)
            idx[id(i, j)] = pii(i, j);
    for (int i = 0; i < n; ++i) add(id(i, i), id(i + 1, i + 1));
    for (int i = 1; i <= n; ++i) {
        static int x, y, dir; 
        x = 0, y = 0;
        for (int j = 1; j <= n; ++j) {
            dir = d[x];
            if (x == a[i] - 1) d[x] = 0, dir = 0;
            if (x >= a[i] - 1) add(id(x, y), id(x + dx[dir], y + dy[dir])); 
            x += dx[dir], y += dy[dir];
        }
    }
    dfs(id(0, 0), 0);
    scanf("%d", &q);
    while (q--) {
        static int r1, c1, r2, c2;
        scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
        auto p = reid(lca(id(r1, c1), id(r2, c2)));
        printf("%d %d\n", p.first, p.second);
    } return 0;
}