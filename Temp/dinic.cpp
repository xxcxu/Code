#include <bits/stdc++.h>

static const int N = 105, inf = 1000000007;

int m, n;

FILE *fin, *fout, *ferr;

class MaxFlow
{
    static const int M = 10005 * 2;

public:
    int s, t, cnt;
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
    fscanf(fin, "%d%d", &m, &n);
    Dinic.s = 0, Dinic.t = n + 1;
    Dinic.init();
    while (true)
    {
        static int u, v;
        fscanf(fin, "%d%d", &u, &v);
        if (u == -1 && v == -1)
            break;
        Dinic.add_edge(u, v, inf);
    }
    for (int i = 1; i <= m; ++i)
        Dinic.add_edge(Dinic.s, i, 1);
    for (int i = m + 1; i <= n; ++i)
        Dinic.add_edge(i, Dinic.t, 1);
    int dis = Dinic.dinic();
    if (dis == 0)
        return fputs("No Solution!\n", stdout), 0;
    fprintf(fout, "%d\n", dis);
    for (int i = 0; i <= Dinic.cnt; i += 2)
    {
        fprintf(ferr, "%d %d %d\n", i, Dinic.e[i ^ 1].to, Dinic.e[i].to);
        if (Dinic.e[i ^ 1].to != Dinic.s && Dinic.e[i].to != Dinic.t)
            if (Dinic.e[i ^ 1].link != 0)
            {
                fprintf(fout, "%d %d\n", Dinic.e[i].to, Dinic.e[i ^ 1].to);
            }
    }
    return 0;
}