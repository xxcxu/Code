#include <bits/stdc++.h>
#define int long long
#define eb emplace_back
static const int N = 100005, L = 25, inf = 1e9 + 7;
int n, m, P;
int f[3][N], g[3][L][N];
std::vector<int> e[N];
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}
void dfs1(int x, int fa) {
    f[0][x] = 1;
    f[1][x] = f[2][x] = inf;
    for (int y : e[x]) if (y != fa) {
        dfs1(y, x);
        f[2][x] = std::min(std::max(f[2][x], f[2][y] + 1), std::max(f[1][x], f[1][y]));
        f[1][x] = std::min(std::max(f[1][x], f[2][y] + 1), std::max(f[0][x], f[1][y]));
        f[0][x] = std::max(f[0][x], f[2][y] + 1);
    }
    f[1][x] = std::min(f[0][x], f[1][x]);
    f[2][x] = std::min(f[1][x], f[2][x]);
}
void dfs2(int x, int fa) {
    int cnt = f[2][1];
    for (int i = 1; i <= cnt; ++i) g[0][i][x] = 1;
    for (int y : e[x]) if (y != fa) {
        dfs2(y, x);
        for (int i = 1; i <= cnt; ++i) {
            g[2][i][x] = inc(mul(g[2][i][x], g[2][i - 1][y]), mul(g[1][i][x], g[1][i][y]));
            g[1][i][x] = inc(mul(g[1][i][x], g[2][i - 1][y]), mul(g[0][i][x], g[1][i][y]));
            g[0][i][x] = mul(g[0][i][x], g[2][i - 1][y]);
        }
    }   
    for (int i = 1; i <= cnt; ++i)
        g[1][i][x] = inc(g[1][i][x], g[0][i][x]),
        g[2][i][x] = inc(g[2][i][x], g[1][i][x]);
}
signed main() {
    scanf("%lld%lld%lld", &n, &m, &P);
    if (m != n - 1) return puts("-1\n-1"), 0;
    for (int i = 1; i <= m; ++i) {
        static int u, v;
        scanf("%lld%lld", &u, &v);
        e[u].eb(v); e[v].eb(u);
    }
    dfs1(1, 0); dfs2(1, 0);
    printf("%lld\n", f[2][1] - 1);
    printf("%lld\n", g[2][f[2][1]][1]);
    return 0;
}    
// 1308