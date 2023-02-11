#include <bits/stdc++.h>
int read() {
    int t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}
#define eb emplace_back
using ull = unsigned long long;
static const int N = 5005, M = 205, P = 5243;
int d, n, m, ans, f[M][N], s[M][N];
ull p[M], h[N];
std::vector<int> e[M][N];
std::unordered_map<ull, int> map;
void dfs(int k, int x, int fa) {
    ans -= 2 * (-- map[h[x]]) + 1;
    h[x] += p[k] * ull(fa - f[k][x]);
    ans += 2 * (++ map[h[x]]) - 1;
    f[k][x] = fa;
    for (int y : e[k][x])
        if (f[k][y] != fa) dfs(k, y, fa);
}
void add(int k, int x, int y) {e[k][x].eb(y);}
signed main() {
    d = read(), n = read(), m = read();
    ans = n;
    for (int i = p[0] = 1; i <= d; ++i) p[i] = p[i - 1] * P;
    for (int i = 1; i <= d; ++i) {
        for (int j = 1; j <= n; ++j) f[i][j] = j, s[i][j] = 1;
        for (int j = 1; j <= n; ++j) h[j] += p[i] * j;
    }
    for (int i = 1; i <= n; ++i) ++ map[h[i]];
    for (int i = 1; i <= m; ++i) {
        static int a, b, k;
        a = read(), b = read(), k = read();
        if (f[k][a] != f[k][b]) {
            static int x, y;
            x = a, y = b;
            a = f[k][a], b = f[k][b];
            if (s[k][a] > s[k][b]) std::swap(a, b), std::swap(x, y);
            s[k][b] += s[k][a];
            dfs(k, x, f[k][y]);
            add(k, x, y); add(k, y, x);
        }
        printf("%d\n", ans);
    }
    return 0;
}