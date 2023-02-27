#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static constexpr int N = 1'005, E = 11'005, inf = 0x3f3f3f3f;

int n, m, s, t, V, cnt = -1;
int a[N], dist[N], flow[E << 1], head[N];
bool vis[N];

class edge
{
public:
    int to, f, cost, next;
    edge(int to = 0, int f = 0, int cost = 0, int next = 0) : to(to), f(f), cost(cost), next(next) {}
} e[E << 1];

void add_edge(int u, int v, int f, int c)
{
    e[++cnt] = edge(v, f, c, head[u]);
    head[u] = cnt;
    e[++cnt] = edge(u, 0, -c, head[v]);
    head[v] = cnt;
}

bool spfa()
{
    for (int i = 0; i <= V; ++i)
        dist[i] = inf, vis[i] = false;
    std::queue<int> q;
    dist[t] = 0, vis[t] = 1;
    q.emplace(t);
    while (q.size())
    {
        int x = q.front();
        q.pop();
        vis[x] = false;
        for (int i = head[x]; ~i; i = e[i].next)
        {
            if (e[i ^ 1].f > flow[i ^ 1] && dist[e[i].to] > dist[x] - e[i].cost)
            {
                dist[e[i].to] = dist[x] - e[i].cost;
                if (!vis[e[i].to])
                    vis[e[i].to] = true, q.emplace(e[i].to);
            }
        }
    }
    return dist[s] < inf;
}

int dfs(int x, int cf, int &cost)
{
    vis[x] = true;
    if (x == t || !cf)
        return cf;
    int getf = 0;
    for (int i = head[x]; ~i; i = e[i].next)
    {
        if (!vis[e[i].to] && e[i].f > flow[i] && dist[e[i].to] == dist[x] - e[i].cost)
        {
            int nf = dfs(e[i].to, std::min(cf, e[i].f - flow[i]), cost);
            if (nf)
            {
                flow[i] += nf, flow[i ^ 1] -= nf;
                getf += nf, cf -= nf;
                cost += nf * e[i].cost;
                if (!cf)
                    break;
            }
        }
    }
    return getf;
}

void mcmf(int &cost, int &flow)
{
    cost = flow = 0;
    while (spfa())
    {
        vis[t] = true;
        while (vis[t])
        {
            std::memset(vis, 0, (V + 1) * sizeof(bool));
            flow += dfs(s, inf, cost);
        }
    }
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d%d", &n, &m);
    s = 0, t = V = n + 2;
    std::memset(head, -1, sizeof head);
    add_edge(s, 1, inf, 0);
    add_edge(n + 1, t, inf, 0);

    for (int i = 1; i <= n; ++i)
    {
        static int x;
        fscanf(fin, "%d", &x);
        add_edge(i, i + 1, inf - x, 0);
    }
    for (int i = 1; i <= m; ++i)
    {
        static int s, t, c;
        fscanf(fin, "%d%d%d", &s, &t, &c);
        add_edge(s, t + 1, inf, c);
    }
    int mincost, maxflow;
    mcmf(mincost, maxflow);
    fprintf(fout, "%d\n", mincost);
    return 0;
}