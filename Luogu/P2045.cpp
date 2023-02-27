#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static constexpr int N = 5'005, E = 10'005, inf = 0x3f3f3f3f;
int n, k, s, t, V, cnt = 1;
int a[N][N];

int dist[N], flow[E << 1], head[N];
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

int get(int i, int j) { return (i - 1) * n + j; }

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;

    fscanf(fin, "%d%d", &n, &k);

    int add = n * n;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            fscanf(fin, "%d", a[i] + j);

    s = 0, t = V = 2 * add + 1;
    std::memset(head, -1, (V + 1) * sizeof(int));

    add_edge(s, get(1, 1), k, 0);
    add_edge(get(n, n) + add, t, k, 0);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            add_edge(get(i, j), get(i, j) + add, 1, -a[i][j]);
            add_edge(get(i, j), get(i, j) + add, k - 1, 0);
            if (i + 1 <= n)
                add_edge(get(i, j) + add, get(i + 1, j), k, 0);
            if (j + 1 <= n)
                add_edge(get(i, j) + add, get(i, j + 1), k, 0);
        }

    int mincost = 0, maxflow = 0;
    mcmf(mincost, maxflow);
    fprintf(fout, "%d\n", -mincost);

    return 0;
}