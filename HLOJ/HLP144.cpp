#include <bits/stdc++.h>
#define eb emplace_back
using ll = long long;
static constexpr int N = 2e5 + 5;
static constexpr ll inf = 1e18;
struct node {
    int from, ver, cost, heal;
    node(int from = 0, int ver = 0, int cost = 0, int heal = 0):
        from(from), ver(ver), cost(cost), heal(heal) {}
};
struct Node {
    int id; ll dis;
    Node(int id = 0, ll dis = 0): id(id), dis(dis) {}
    friend bool operator < (const Node &a, const Node &b) {return a.dis > b.dis;}
};
int n, m, scc_cnt, time_stamp, bel[N], dfn[N], low[N], indeg[N];
std::vector<node> E[N], G[N], edge[N];
ll h[N], dis[N];
bool vis[N];
void dijkstra() {
    static std::priority_queue<Node> q;
    q.push(Node(1, dis[1] = 0));
    while (q.size()) {
        int u = q.top().id; q.pop();
        if (vis[u]) continue; vis[u] = true;
        for (auto v : E[u]) {
            const int &to = v.ver, &cost = v.cost, &heal = v.heal;
            if (dis[to] > dis[u] + cost) dis[to] = dis[u] + cost, q.emplace(Node(to, dis[to]));
        }
    }
}
void topsort() {
    static std::queue<int> q;
    for (int i = 1; i <= scc_cnt; ++i) if (!indeg[i]) q.emplace(i);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (auto v : edge[u]) {
            const int &to = v.ver, &cost = v.cost, &heal = v.heal;
            h[to] = std::max(h[to], h[u] + heal);
            if (!(--indeg[to])) q.emplace(to); 
        }
    }
}
void tarjan(int x) {
    static int top = 0, stack[N] = {};
    static bool instack[N] = {};
    dfn[x] = low[x] = ++ time_stamp;
    stack[++ top] = x; instack[x] = true;
    for (auto y : G[x]) {
        const int &to = y.ver, &cost = y.cost, &heal = y.heal;
        if (!dfn[to]) tarjan(to), low[x] = std::min(low[x], low[to]);
        else if (instack[to]) low[x] = std::min(low[x], dfn[to]);
    }
    if (dfn[x] == low[x]) {
        ++ scc_cnt; static int u;
        do {
            u = stack[top --];
            bel[u] = scc_cnt;
            instack[u] = false;
        } while (u != x);
    }
}
void clear() {
    scc_cnt = 0; time_stamp = 0;
    for (int i = 1; i <= n; ++i) indeg[i] = 0, low[i] = 0, bel[i] = 0;
    for (int i = 1; i <= n; ++i) E[i].clear(), G[i].clear(), edge[i].clear();
    for (int i = 1; i <= n; ++i) h[i] = 0, dis[i] = inf, vis[i] = false, dfn[i] = 0;
}
void solve() {
    scanf("%d%d", &n, &m); clear();
    for (int i = 1; i <= m; ++i) {
        static int u, v, e, p;
        scanf("%d%d%d%d", &u, &v, &e, &p);
        E[u].eb(u, v, e, p);
    }
    dijkstra();
    for (int i = 1; i <= n; ++i)
        for (auto j : E[i])
            if (dis[j.ver] == dis[i] + j.cost) G[i].eb(j);
    tarjan(1);
    for (int i = 1; i <= n; ++i)
        for (auto j : G[i]) {
            const int &to = j.ver, &cost = j.cost, &heal = j.heal;
            if (bel[i] != bel[to]) 
                edge[bel[i]].eb(bel[i], bel[to], cost, heal), ++indeg[bel[to]];
        }
    topsort();
    printf("%lld %lld\n", dis[n], h[bel[n]]);
}
signed main() {
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}