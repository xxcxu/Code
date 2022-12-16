#include <bits/stdc++.h>

static constexpr int N = 3e3 + 5, E = 1e5 + 5, inf = INT_MAX;
int n, m, s, t, V, cnt = -1, dist[N], flow[E << 1], head[N];
bool vis[N];

class edge {
    public: int to, f, cost, next;
    public: edge(int to = 0, int f = 0, int cost = 0, int next = 0):
        to(to), f(f), cost(cost), next(next) {}
} e[E << 1];

void add_edge(int u, int v, int f, int c) {
    e[++ cnt] = edge(v, f, c, head[u]); head[u] = cnt;
    e[++ cnt] = edge(u, 0, -c, head[v]); head[v] = cnt;
}

bool bfs() {
    for (int i = 1; i <= V; ++i) dist[i] = inf, vis[i] = false;
    std::queue<int> q;
    dist[t] = 0, vis[t] = 1;
    q.emplace(t);
    while (q.size()) {
        int x = q.front(); q.pop();
        vis[x] = false;
        for (int i = head[x]; ~i; i = e[i].next) {
            if (e[i ^ 1].f > flow[i ^ 1] && dist[x] > dist[e[i].to] + e[i].cost) {
                dist[e[i].to] = dist[x] - e[i].cost;
                if (!vis[e[i].to]) vis[e[i].to] = true, q.emplace(e[i].to);
            }
        }
    } return dist[s] < inf;
}

int dfs(int x, int cf, int &cost) {
    vis[x] = true;
    if (x == t || !cf) return cf;
    int getf = 0;
    for (int i = head[x]; ~i; i = e[i].next) {
        if (!vis[e[i].to] && e[i].f > flow[i] && dist[e[i].to] == dist[x] - e[i].cost) {
            int nf = dfs(e[i].to, std::min(cf, e[i].f - flow[i]), cost);
            if (nf) {
                flow[i] += nf, flow[i ^ 1] -= nf;
                getf += nf, cf -= nf;
                cost += nf * e[i].cost;
                if (!cf) break;
            }
        }
    } return getf;
}

void mcmf(int &cost, int &flow) {
    cost = flow = 0;
    while (bfs()) {
        vis[t] = true;
        while (vis[t]) {
            std::memset(vis, 0, (V + 1) * sizeof(bool));
            flow += dfs(s, inf, cost);
        }
    }   
}

signed main() {
    scanf("%d%d", &m, &n);
    s = n + n * m + 1;
    t = V = s + 1;
    std::memset(head, -1, (V + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            static int t;
            scanf("%d", &t);
            for (int k = 1; k <= n; ++k)
                add_edge(i, j * n + k, 1, t * k);
        }
    }
    for (int i = 1; i <= n; ++i) add_edge(s, i, 1, 0);
    for (int i = n + 1; i <= n * m + n; ++i) add_edge(i, t, 1, 0);
    int mincost = 0, maxflow = 0;
    mcmf(mincost, maxflow);
    printf("%.2lf\n", 1.0 * mincost / n);
    return 0;
}