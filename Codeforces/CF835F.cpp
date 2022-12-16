#include <bits/stdc++.h>
#define int long long
using pii = std::pair<int, int>;
static constexpr int N = 2e5 + 5;
int n, cur = 1e18 + 7, ans, sum, edge_cnt = 1;
int head[N], dp[N], len[N];
bool vis[N], pos[N];
std::vector<int> ring;
std::multiset<pii> s1, s2;
class Edge{
    public: int ver, link, next;
    public: ~Edge() {ver = 0, link = 0, next = 0}
    public: Edge(int ver = 0, int link = 0, int next = 0):
        ver(ver), link(link), next(next) {}
    private: bool operator < (const Edge &a) {return link < a.link;}
} e[N << 1];
auto Add(int x, int y, int z = 1) -> void {
    e[++ edge_cnt] = Edge(y, z, head[x]);
    head[x] = edge_cnt;
}
auto Dfs(int x, int last) -> int {
    vis[x] = true;
    for (int i = head[x]; i; i = e[i].next) {
        const int &y = e[i].ver;
        if (i != (last ^ 1))
            if (!vis[y]) {
                int t = Dfs(y, i);
                if (t) return t == x ? 0 : t;
            } else return y;
    } return vis[x] = 0;
}
auto Dfs2(int x, int fa) -> void {
    if (vis[x]) ring.emplace_back(x);
    pos[x] = 1;
    for (int i = head[x]; i; i = e[i].next) {
        const int &y = e[i].ver, &z = e[i].link;
        if (!vis[y] && y != fa) {
            Dfs2(y, x);
            ans = std::max(ans, dp[x] + dp[y] + z);
            dp[x] = std::max(dp[x], dp[y] + z);
        } else
            if (vis[y] && !pos[y]) {
                // len[y] = len[x] + z;
                len[y] = dp[x] + z;
                Dfs2(y, x);
            }
    }
}
auto Solve() -> void {
    for (int i = 0; i < (int)ring.size(); ++i) {
        s1.emplace(dp[ring[i]] + len[ring[i]], i);
        s2.emplace(dp[ring[i]] - len[ring[i]], i);
    }
    for (int i = 0; i < (int)ring.size(); ++i) {
        auto it1 = --(s1.end()), it2 = --(s2.end());
        if (it1 -> second == it2 -> second) {
            int t = (-- it1) -> first + it2 -> first;
            int p = (++ it1) -> first + (-- it2) -> first;
            cur = std::min(cur, std::max(t, p));
        } else
            cur = std::min(cur, it1 -> first + it2 -> first);
        s1.erase(s1.find(pii(dp[ring[i]] + len[ring[i]], i)));
        s2.erase(s2.find(pii(dp[ring[i]] - len[ring[i]], i)));
        s1.emplace(dp[ring[i]] + len[ring[i]] + sum , i);
        s2.emplace(dp[ring[i]] - len[ring[i]] - sum , i);
    }
}
auto main() -> decltype(0) {
    scanf("%lld", &n);
    for (int i = 1, u, v, w; i <= n; ++i) {
        scanf("%lld%lld%lld", &u, &v, &w);
        Add(u, v, w);
        Add(v, u, w);
    }
    Dfs(1, -1);
    for (int i = 1; i <= n; ++i)
        if (vis[i]) {
            Dfs2(i, -1);
            break;
        }
    for (int i = 0; i < (int)ring.size(); ++i)
        for (int j = head[ring[i]]; j; j = e[j].next) {
            const int &y = e[j].ver, &z = e[j].link;
            if (y == ring[(i + 1) % (int)(ring.size())]) {
                sum += z;
                if ((int)ring.size() > 2) break;
            }
    }
    if ((int)ring.size() == 2) sum >>= 1;
    Solve();
    printf("%lld\n", std::max(ans, cur));
    return 0;
}