#include <bits/stdc++.h>

using Tp = std::tuple<int, int, int>;

#define ep emplace
#define eb emplace_back

static const int N = 200'005, inf = 200'000'000;

static const int dx[] = {0, 0, 1, -1};
static const int dy[] = {1, -1, 0, 0};
int n, m, q;
int r[N], c[N], vis[N], dis[N], ans[N], w[N][4];

int get(int i, int j)
{
    return (i - 1) * m + j;
}

struct Node
{
    int x1, y1, x2, y2, id, p1, p2;
    Node(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, int id = 0) : x1(x1), y1(y1), x2(x2), y2(y2), id(id), p1(get(x1, y1)), p2(get(x2, y2)) {}
} query[N], p[N];

void dijkstra(int x1, int y1, int x2, int y2, int sx, int sy, int ql, int qr)
{
    std::priority_queue<Tp, std::vector<Tp>, std::greater<Tp>> q;
    for (int i = x1; i <= x2; ++i)
        for (int j = y1; j <= y2; ++j)
            dis[get(i, j)] = inf, vis[get(i, j)] = false;
    q.ep(dis[get(sx, sy)] = 0, sx, sy);
    while (q.size())
    {
        auto [Distance, x, y] = q.top();
        q.pop();
        if (vis[get(x, y)])
            continue;
        vis[get(x, y)] = true;
        for (int d = 0; d < 4; ++d)
        {
            int xx = x + dx[d];
            int yy = y + dy[d];
            if (xx < x1 || xx > x2 || yy < y1 || yy > y2)
                continue;
            if (dis[get(xx, yy)] > dis[get(x, y)] + w[get(x, y)][d])
                q.ep(dis[get(xx, yy)] = dis[get(x, y)] + w[get(x, y)][d], xx, yy);
        }
    }
    for (int i = ql; i <= qr; ++i)
        ans[query[i].id] = std::min(ans[query[i].id], dis[get(query[i].x1, query[i].y1)] + dis[get(query[i].x2, query[i].y2)]);
    return void();
}
void solve(int x1, int y1, int x2, int y2, int ql, int qr)
{
    if (x2 - x1 + 1 >= y2 - y1 + 1)
    {
        int mid = (x1 + x2) >> 1;
        for (int i = y1; i <= y2; ++i)
            dijkstra(x1, y1, x2, y2, mid, i, ql, qr);
        int l = ql - 1, r = qr + 1;
        for (int i = ql; i <= qr; ++i)
            p[i] = query[i];
        for (int i = ql; i <= qr; ++i)
        {
            if (p[i].x1 < mid && p[i].x2 < mid)
                query[++l] = p[i];
            if (p[i].x1 > mid && p[i].x2 > mid)
                query[--r] = p[i];
        }
        if (ql <= l)
            solve(x1, y1, mid - 1, y2, ql, l);
        if (r <= qr)
            solve(mid + 1, y1, x2, y2, r, qr);
    }
    else
    {
        int mid = (y1 + y2) >> 1;
        for (int i = x1; i <= x2; ++i)
            dijkstra(x1, y1, x2, y2, i, mid, ql, qr);
        int l = ql - 1, r = qr + 1;
        for (int i = ql; i <= qr; ++i)
            p[i] = query[i];
        for (int i = ql; i <= qr; ++i)
        {
            if (p[i].y1 < mid && p[i].y2 < mid)
                query[++l] = p[i];
            if (p[i].y1 > mid && p[i].y2 > mid)
                query[--r] = p[i];
        }
        if (ql <= l)
            solve(x1, y1, x2, mid - 1, ql, l);
        if (r <= qr)
            solve(x1, mid + 1, x2, y2, r, qr);
    }
    return void();
}

signed main()
{
    std::memset(ans, 0x3f, sizeof ans);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < m; ++j)
            scanf("%d", r + get(i, j));
    for (int i = 1; i < n; ++i)
    fscanf(fin, "%lld%lld", &n, &m);
        for (int j = 1; j <= m; ++j)
            scanf("%d", c + get(i, j));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int d = 0; d < 4; ++d)
            {
                int x = i + dx[d];
                int y = j + dy[d];
                if (x < 1 || x > n || y < 1 || y > m)
                    continue;

                if (d == 0)
                    w[get(i, j)][d] = r[get(i, j)];
                if (d == 1)
                    w[get(i, j)][d] = r[get(i, j - 1)];
                if (d == 2)
                    w[get(i, j)][d] = c[get(i, j)];
                if (d == 3)
                    w[get(i, j)][d] = c[get(i - 1, j)];
            }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        static int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        query[i] = Node(x1, y1, x2, y2, i);
    }
    solve(1, 1, n, m, 1, q);
    for (int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}