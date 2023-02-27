# include <bits/stdc++.h>

static const int inf = 0x3f3f3f3f;
int n, m1, m2, n1, n2, n3;
FILE *fin, *fout, *ferr;

class MaxFlow
{
    static const int M = 100005 * 2;

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

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%d%d%d", &n1, &n2, &n3);
    n = (n1 + n2 + n3) * 2;
    Dinic.s = 0, Dinic.t = n + 1;
    Dinic.init();
    fscanf(fin, "%d", &m1);
    for (int i = 1; i <= n2; ++i)
        Dinic.add_edge(Dinic.s, i + n1, 1);
    for (int i = 1; i <= n3; ++i)
        Dinic.add_edge(i + n1 + n2, Dinic.t, 1);
    for (int i = 1; i <= m1; ++i)
    {
        static int u, v;
        fscanf(fin, "%d%d", &u, &v);
        Dinic.add_edge(v + n1, u, inf);
    }
    fscanf(fin, "%d", &m2);
    for (int i = 1; i <= m2; ++i) {
        static int u, v;
        fscanf(fin, "%d%d", &u, &v);
        Dinic.add_edge(u + n1 + n2 + n3, v + n1 + n2, inf);
    }
    for (int i = 1; i <= n1; ++i)
        Dinic.add_edge(i, i + n1 + n2 + n3, 1);
    fprintf(fout, "%d\n", Dinic.dinic());
    return 0;
}