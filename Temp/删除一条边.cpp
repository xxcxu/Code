#include<bits/stdc++.h>
#define int long long
#define eb emplace_back
using pii = std::pair<int, int>;
static const int N = 400005, inf = 2e9;
int n, m, l;
int u[N], v[N], w[N], L[N], R[N], d1[N], d2[N], tr[N << 2], id[N], ans[N], path[N];
bool vis[N];
class node {
    public: int to, link, id;
    public: node(int to = 0, int link = 0, int id = 0): to(to), link(link), id(id) {}
};
std::vector<node> e[N];
void dijkstra(int s, int *dis) {
    for (int i = 1; i <= n; ++i) dis[i] = inf;
    std::memset(vis, 0, sizeof vis);
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    q.emplace(dis[s] = 0, s);
    while (q.size()) {
        int x = q.top().second; q.pop();
        if (vis[x]) continue; vis[x] = true;
        for (auto [y, z, id] : e[x])
            if (dis[y] > dis[x] + z) q.emplace(dis[y] = dis[x] + z, y);
    }
}
void bfs(int s, int *dis, int *dp) {
    std::queue<int> q;
    q.emplace(path[s]); dp[path[s]] = s;
    while (q.size()) {
        int x = q.front(); q.pop();
        for (auto [y, z, ignore] : e[x])
            if (!id[y] && !dp[y] && dis[x] + z == dis[y])
                dp[y] = s, q.emplace(y);
    }
}
#define ls (x << 1)
#define rs (x << 1 | 1)
void build(int x, int l, int r) {
    tr[x] = inf;
    if (l == r) return void();
    int mid = (l + r) >> 1;
    build(ls, l, mid); build(rs, mid + 1, r);
    return void();
}
void modify(int x, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) return tr[x] = std::min(tr[x], v), void();
    int mid = (l + r) >> 1;
    if (ql <= mid) modify(ls, l, mid, ql, qr, v);
    if (qr >  mid) modify(rs, mid + 1, r, ql, qr, v);
}
void update(int x, int l, int r) {
    if (l == r) return ans[l] = tr[x], void();
    int mid = (l + r) >> 1;
    tr[ls] = std::min(tr[ls], tr[x]);
    tr[rs] = std::min(tr[rs], tr[x]);
    update(ls, l, mid), update(rs, mid + 1, r);
}
signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%lld%lld%lld", u + i, v + i, w + i);
        e[u[i]].eb(v[i], w[i], i * 2);
        e[v[i]].eb(u[i], w[i], i * 2 + 1);
    }
    dijkstra(1, d1);
    dijkstra(n, d2);
    int now = 1;    
    std::memset(vis, 0, sizeof vis);
    while (now != n) {
        path[++ l] = now, id[now] = l;
        for (auto [to, link, id] : e[now])
            if (d2[to] + link == d2[now]) {
                vis[id] = true, now = to;
                break;
            }
    }
    path[++ l] = n, id[n] = l;
    for (int i = 1; i <= l; ++i) bfs(i, d1, L), bfs(i, d2, R);
    -- l;

    build(1, 1, l);
    for (int i = 1; i <= n; ++i)
        for (auto [j, k, id] : e[i])
            if (!vis[id] && L[i] < R[j]) 
                modify(1, 1, l, L[i], R[j] - 1, d1[i] + d2[j] + k);
    update(1, 1, l);
    int res = 0, plan = 0;
    for (int i = 1; i <= l; ++i) 
        if (ans[i] > res) res = ans[i], plan = 1;
        else if (ans[i] == res) ++ plan;
    if (res == d1[n]) plan = m;
    return printf("%lld %lld\n", res, plan), 0;
}