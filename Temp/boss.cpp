#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 2'005;
static const long double eps = 0.000'000'01;

int n, m, c;
long double f[N][N];
long double p, q;

bool check(long double v)
{
    f[0][0] = 0;
    for (int i = 1; i <= m; ++i)
        f[0][i] = v;
    for (int i = 1; i <= n; ++i)
    {
        f[i][0] = 0;
        for (int j = 1; j <= m; ++j)
        {
            f[i][j] = std::min(v, p * f[i][j - 1] + q * f[i - 1][j] + 1);
        }
    }
    return f[n][m] + eps <= v;
}

signed main()
{
    // fin = stdin;
    // fout = stdout;
    // ferr = stderr;
    fin = fopen("boss.in", "r");
    fout = fopen("boss.out", "w+");
    ferr = fopen("boss.out", "w+");
    fscanf(fin, "%d%d%d", &n, &m, &c);
    p = 1.0 * c / 100;
    q = 1.0 - p;
    long double l = 1, r = 1'000'000'000;
    for (int i = 1; i <= 80; ++i)
    {
        long double mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    fprintf(fout, "%.8Lf\n", (l + r) / 2);
    return 0;
}