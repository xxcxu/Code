#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
static constexpr int N = 1e5 + 5;
int n, q, p[N], f[N], dfn[N], rnk[N], anc[N][26];
std::vector<int> e[N];
std::set<int> set;
void cmin(int &x, int y) {if (y < x) x = y;}
void cmax(int &x, int y) {if (y > x) x = y;}
void dfs1(int x) {
    f[x] = x;
    for (int y : e[x]) dfs1(y), cmin(f[x], f[y]);
}
void dfs2(int x) {
    static int time_stamp = 0;
    for (int y : e[x]) dfs2(y);
    dfn[x] = ++ time_stamp;
    rnk[time_stamp] = x;
}
signed main() {
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%d", p + i), anc[i][0] = p[i];
    for (int j = 1; j <= 25; ++j)
        for (int i = 1; i <= n; ++i)
            anc[i][j] = anc[anc[i][j - 1]][j - 1];
    for (int i = 1; i <= n; ++i) e[p[i]].emplace_back(i);
    dfs1(0); 
    for (int i = 1; i <= n; ++i) std::sort(all(e[i]), [&](int a, int b) {return f[a] < f[b];});
    dfs2(0);
    for (int i = 1; i <= n; ++i) set.insert(i);
    for (int i = 1; i <= q; ++i) {
        static int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1) {
            while (-- x) set.erase(*set.begin());
            printf("%d\n", rnk[*set.begin()]);
            set.erase(*set.begin());
        }
        if (op == 2) {
            int ans = 0;
            for (int i = 25; i >= 0; --i)
                if (anc[x][i] && set.find(dfn[anc[x][i]]) == set.end()) x = anc[x][i], ans += 1 << i;
            set.emplace(dfn[x]);
            printf("%d\n", ans);
        }
    }
    return 0;
}