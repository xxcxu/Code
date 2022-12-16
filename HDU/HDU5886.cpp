#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define int long long
using pii = std::pair<int, int>;
const int N = 2e5 + 5;
int n, cnt, root, len, ans, s, t;
int l[N], r[N], path[N], vis[N], c[N], c1[N];
std::vector<pii> e[N];
bool find;
auto Clear() -> void {
    cnt = 0;
    std::memset(l, 0, sizeof l);
    std::memset(r, 0, sizeof r);
    std::memset(c, 0, sizeof c);
    std::memset(c1, 0, sizeof c1);
    std::memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; ++i) e[i].clear();
}
auto Dfs1(int x, int fa, int d) -> void {
    if (d > len) root = x, len = d;
    for (auto it : e[x]) {
        int y = it.first, z = it.second;
        if (y == fa) continue;
        Dfs1(y, x, d + z);
    }
}
auto Dfs2(int s, int t, int fa, int d) -> int {
    if (s == t) {find = true; return t;}
    for (auto it : e[s]) {
        int y = it.first, z = it.second;
        if (y == fa) continue;
        int p = Dfs2(y, t, s, d + z);
        if (find) {
            ++ cnt;
            vis[p] = true;
            c[cnt] = d + z;
            // c[i]是从直径的起点到path[i]所用的距离
            path[cnt] = p;
            return s;
        }
    } return s;
}
auto Dfs3(int x, int fa) -> int {
    int max = 0;
    for (auto it : e[x]) {
        int y = it.first, z = it.second;
        if (vis[y] || y == fa) continue;
        max = std::max(max, Dfs3(y, x) + z);
    } return max;
}
auto main() -> decltype(0) {
    int T; scanf("%lld", &T);
    while (T--) {
        scanf("%lld", &n);
        Clear();
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%lld%lld%lld", &u, &v, &w);
            e[u].emplace_back(v, w);
            e[v].emplace_back(u, w);
        }
        len = 0; Dfs1(1, 0, 0); s = root;
        len = 0; Dfs1(s, 0, 0); t = root;
        ans = 0;
        find = false; Dfs2(s, t, -1, 0);
        path[++ cnt] = s; vis[s] = true;
        // path存了直径上的点
        ans += len * (n - cnt); // 没有切断直径 最长的仍是直径 (n-1)-(cnt-1)=n-cnt
        for (int i = 2; i <= cnt; ++i) c1[i] = Dfs3(path[i], -1); // c1[i]表示path[i]能走到的最深深度
        for (int i = 1; i <= cnt; ++i) l[i] = std::max(len - c[i] + c1[i], l[i - 1]); // l 是左半部分
        for (int i = cnt; i >= 1; --i) r[i] = std::max(c[i] + c1[i], r[i + 1]); // r 是右半部分
        for (int i = 1; i < cnt; ++i) ans += std::max(l[i], r[i + 1]); // 扫一遍直径上的边，i是左半部分，i+1是右半部分
        printf("%lld\n", ans);
    } return 0;
}