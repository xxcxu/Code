# include <bits/stdc++.h>

static const int N = 25, inf = 0x3f3f3f3f;
FILE *fin, *fout, *ferr;
int n, r, c, d, sum;
char h[N][N], map[N][N];
class MaxFlow
{
    static const int M = 400005 * 4;

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
        // fprintf(ferr, "%d %d %d\n", x, y, z);
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

int get(int i, int j) { return (i - 1) * c + j; }
int dis(int i, int j, int x, int y) {
    return (i - x) * (i - x) + (j - y) * (j - y);
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%d%d%d", &r, &c, &d);
    n = r * c * 2;
    Dinic.s = 0, Dinic.t = n + 1;
    Dinic.init();
    for (int i = 1; i <= r; ++i)
        fscanf(fin, "%s", h[i] + 1);
    for (int i = 1; i <= r; ++i)
        fscanf(fin, "%s", map[i] + 1);
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            if (h[i][j] != '0')
                Dinic.add_edge(get(i, j), get(i, j) + n / 2, h[i][j] - '0');
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            if (map[i][j] == 'L')
                ++ sum, Dinic.add_edge(Dinic.s, get(i, j), 1);
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            for (int x = 1; x <= r; ++x)
                for (int y = 1; y <= c; ++y)
                    if (i != x || j != y)
                        if (dis(i, j, x, y) <= d * d)
                            Dinic.add_edge(get(i, j) + n / 2, get(x, y), inf);
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            if (i - d <= 0 || i + d > r || j - d <= 0 || j + d > c)
                Dinic.add_edge(get(i, j) + n / 2, Dinic.t, inf);
    fprintf(fout, "%d\n", sum - Dinic.dinic());
    return 0;
}