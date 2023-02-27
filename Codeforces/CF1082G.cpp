#include <bits/stdc++.h>

#define int long long

FILE *fin, *fout, *ferr;

static const int N = 1005, inf = 0x3f3f3f3f;

int n, m, a[N];

class MaxFlow
{
public:
    static const int M = 5005 * 2;
    int n, s, t, cnt;
    class Edge
    {
    public:
        int to, link, next;
        Edge(int to = 0, int link = 0, int next = 0) : to(to), link(link), next(next) {}
    } e[M];
#define ep emplace
#define eb emplace_back
    void init()
    {
        cnt = -1;
        std::memset(head, -1, sizeof head);
        return void();
    }
    void insert(int x, int y, int z)
    {
        e[++cnt] = Edge(y, z, head[x]);
        head[x] = cnt;
    }
    void add_edge(int x, int y, int z)
    {
        insert(x, y, z);
        insert(y, x, 0);
    }
    int bfs()
    {
        std::queue<int> q;
        std::memset(dep, 0, sizeof dep);
        dep[s] = 1;
        q.ep(s);
        while (q.size())
        {
            int x = q.front();
            q.pop();
            for (int i = head[x]; ~i; i = e[i].next)
            {
                const int &y = e[i].to;
                const int &z = e[i].link;
                if ((dep[y] == 0) && (z > 0))
                {
                    dep[y] = dep[x] + 1;
                    q.ep(y);
                }
            }
        }
        if (dep[t] > 0)
            return true;
        return false;
    }
    int dfs(int x, int d)
    {
        if (x == t)
            return d;
        for (int &i = cur[x]; ~i; i = e[i].next)
        {
            const int &y = e[i].to;
            const int &z = e[i].link;
            if ((dep[y] == dep[x] + 1) && z != 0)
            {
                int d2 = dfs(y, std::min(d, z));
                if (d2 > 0)
                {
                    e[i].link -= d2;
                    e[i ^ 1].link += d2;
                    return d2;
                }
            }
        }
        return 0;
    }
    int dinic()
    {
        int ans = 0;
        while (bfs())
        {
            for (int i = 0; i <= n + 1; ++i)
                cur[i] = head[i];
            while (int d = dfs(s, inf))
                ans += d;
        }
        return ans;
    }

private:
    int dep[M], cur[M], head[M];
} Dinic;

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");

    int sum = 0;
    fscanf(fin, "%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%lld", a + i);
    Dinic.init();
    Dinic.n = n + m;
    Dinic.s = 0, Dinic.t = n + m + 1;
    for (int i = 1; i <= n; ++i)
        Dinic.add_edge(Dinic.s, i, a[i]);
    for (int i = 1; i <= m; ++i)
    {
        static int u, v, w;
        fscanf(fin, "%lld%lld%lld", &u, &v, &w);
        Dinic.add_edge(u, n + i, inf);
        Dinic.add_edge(v, n + i, inf);
        Dinic.add_edge(n + i, Dinic.t, w);
        sum += w;
    }
    fprintf(fout, "%lld\n", sum - Dinic.dinic());
    return 0;
}