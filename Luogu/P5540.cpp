#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 205, M = 10'005, inf = 2550005;

int n, m, fa[N];
struct Edge
{
    int x, y, a, b, w;
    Edge(int x = 0, int y = 0, int a = 0, int b = 0) : x(x), y(y), a(a), b(b) { w = 0; }
} e[M];
struct Vector2
{
    double x, y;
    Vector2(double x = 0, double y = 0) : x(x), y(y) {}
    double operator()() { return x * y; }
    friend Vector2 operator-(const Vector2 &a, const Vector2 &b) { return Vector2(a.x - b.x, a.y - b.y); }
    friend double operator*(const Vector2 &a, const Vector2 &b) { return a.x * b.y - a.y * b.x; } // 叉积
} ans(inf, inf);

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
Vector2 Kruscal()
{
    std::sort(e + 1, e + m + 1, [&](Edge a, Edge b)
              { return a.w < b.w; });
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    Vector2 res;
    for (int i = 1; i <= m; ++i)
    {
        int fx = find(e[i].x), fy = find(e[i].y);
        if (fx == fy)
            continue;
        fa[fx] = fy;
        res.x += e[i].a, res.y += e[i].b;
    }
    if (ans() > res() || (ans() == res() && res.x > ans.x))
        ans = res;
    return res;
}
void solve(Vector2 A, Vector2 B)
{
    for (int i = 1; i <= m; ++i)
        e[i].w = (B.x - A.x) * e[i].b + (A.y - B.y) * e[i].a;
    Vector2 C = Kruscal();
    if ((B - A) * (C - A) >= 0)
        return void();
    solve(A, C), solve(C, B);
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        static int u, v, a, b;
        fscanf(fin, "%d%d%d%d", &u, &v, &a, &b);
        ++u;
        ++v;
        e[i] = Edge(u, v, a, b);
    }
    for (int i = 1; i <= m; ++i)
        e[i].w = e[i].a;
    Vector2 A = Kruscal();
    for (int i = 1; i <= m; ++i)
        e[i].w = e[i].b;
    Vector2 B = Kruscal();
    solve(A, B);
    return fprintf(fout, "%d %d\n", (int)ans.x, (int)ans.y), 0;
}