#include <bits/stdc++.h>

using pii = std::pair<int, int>;

const int N = 16, inf = 1e9;
int T, n, a[N], vis[N], s[1 << N], f[1 << N][N][N];
class node {
    public: int mask, i, j;
    public: node(int mask = 0, int i = 0, int j = 0): mask(mask), i(i), j(j) {}
} pre[1 << N][N][N];
std::vector<pii> ans;

int find(int x) {
    int ans = 1;
    for (int i = 1; i < x; ++i)
        if (!vis[i]) ++ ans;
    return ans;
}

void calc(int mask, int i, int j) {
    if (!mask) return;
    node status = pre[mask][i][j];
    calc(status.mask, status.i, status.j);
    for (int i = 0; i < n; ++i)
        if (mask - status.mask >> i & 1 && i != j - 1)
            ans.emplace_back(i + 1, j);
}

void solve() {
    ans.clear();
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", a + i);
	
    for (int i = 0; i < 1 << n; ++i)
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k <= n; ++k)
                f[i][j][k] = inf;
    
    f[0][0][0] = 0;

    for (int i = 1; i < 1 << n; ++i)
        for (int j = 0; j < n; ++j)
            if (i >> j & 1) 
                s[i] = s[i - (1 << j)] + a[j];

    int R = (1 << n) - 1;

    for (int i = 0; i < 1 << n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                if (f[i][j][k] < inf) {
                    int c = R ^ i;
                    for (int sta = c; sta; sta = (sta - 1) & c)
                        if (s[sta] > f[i][j][k] && sta >> k) {
                            int lg = __builtin_ctz(sta >> k << k) + 1;
                            if (s[sta] >= f[i + sta][j + 1][lg]) continue;
                            f[i + sta][j + 1][lg] = s[sta];
                            pre[i + sta][j + 1][lg] = (node){i, j, k};
                        }
                }

    for (int i = n; i; --i)
        for (int j = 0; j <= n; ++j)
            if (f[R][i][j] != inf) {
                 calc(R, i, j);
                std::memset(vis, 0, (n + 1) * sizeof(int));
                printf("%d\n", (int)ans.size());
                for (auto it : ans) {
                    printf("%d %d\n", find(it.first), find(it.second));
                    vis[it.first] = true;
                }
                return;
            }
}
signed main() {
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}