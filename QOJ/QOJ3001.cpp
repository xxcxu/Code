#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;
using DB = double;
using LD = long double;

static const int N = 2505;

int n, k;
LD ans, area[N][N], c[N][N];

int pre(int x) { return x == 0 ? n - 1 : x - 1; }
int nxt(int x) { return x == n - 1 ? 0 : x + 1; }
void init(int n)
{
    c[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
}

namespace ComputationGeometry
{
    struct Vector
    {
        LD x, y;
        Vector(LD x = 0.0, LD y = 0.0) : x(x), y(y) {}
        friend Vector operator+(const Vector &a, const Vector &b) { return Vector(a.x + b.x, a.y + b.y); }
        friend Vector operator-(const Vector &a, const Vector &b) { return Vector(a.x - b.x, a.y - b.y); }
        friend LD operator^(const Vector &a, const Vector &b) { return a.x * b.x + a.y * b.y; } // 点积
        friend LD operator*(const Vector &a, const Vector &b) { return a.x * b.y - a.y * b.x; } // 叉积
    };
    LD TriangleArea(Vector a, Vector b, Vector c)
    {
        return std::fabs((b - a) * (c - a)) / 2.0;
    }
}
using namespace ComputationGeometry;

Vector p[N];

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d%d", &n, &k);
    init(n);
    for (int i = 0; i < n; ++i)
        fscanf(fin, "%Lf%Lf", &p[i].x, &p[i].y);
    for (int i = 0; i < n; ++i)
    {
        int j = (i + 2) % n, cnt;
        area[i][j] = TriangleArea(p[i], p[pre(j)], p[j]);
        for (j = nxt(j), cnt = 1; cnt < n - 1; j = nxt(j), ++cnt)
        {
            area[i][j] = area[i][pre(j)] + TriangleArea(p[i], p[pre(j)], p[j]);
        }
    }
    ans = area[0][n - 1];
    for (int i = 0; i < n; ++i)
    {
        for (int j = (i + 2) % n, cnt = 3; cnt <= n - k + 2; j = nxt(j), ++cnt)
        {
            ans -= c[n - cnt][k - 2] / c[n][k] * area[i][j];
        }
    }
    return fprintf(fout, "%.8Lf\n", ans), 0;
}
