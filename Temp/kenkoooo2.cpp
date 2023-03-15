#include <bits/stdc++.h>

using DB = double;
using LD = long double;
using PDD = std::pair<DB, DB>;

#define fi first
#define se second

FILE *fin, *fout, *ferr;

static const int N = 15, M = 1005, inf = 0x3f3f3f3f;

int n, m;
DB f[1 << N], g[1 << N];
DB p[N][M];
PDD a[N];

signed main()
{
    fin = fopen("kenkoooo.in", "r");
    fout = fopen("kenkoooo.out", "w+");

    fscanf(fin, "%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            fscanf(fin, "%lf", p[i] + j);
            p[i][j] /= 100.0;
        }

    for (int i = 1; i <= m; ++i)
    {
        int R = (1 << n) - 1;
        for (int S = 0; S < (1 << n); ++S)
        {
            f[S] = inf;
            g[S] = 1;
            for (int j = 1; j <= n; ++j)
                if (S >> (j - 1) & 1)
                    g[S] *= p[j][i];
        }
        f[0] = 0;
        for (int S = 0; S < (1 << n); ++S)
            for (int j = 0; j < n; ++j)
                if (S >> j & 1)
                    f[S] = std::min(f[S], f[S ^ (1 << j)] + g[S ^ (1 << j)]);
        a[i] = PDD(g[R], (f[R] - g[R] * n) / (1.0 - g[R]));
    }
    std::sort(a + 1, a + m + 1, [&](PDD a, PDD b)
              { return (1.0 - a.fi) * a.se * b.fi < (1.0 - b.fi) * b.se * a.fi; });
    DB ans = 0, now = 1, sum = 0;
    for (int i = 1; i <= m; ++i)
    {
        ans += now * a[i].fi * (sum + n);
        now *= 1.0 - a[i].fi;
        sum += a[i].se;
    }
    fprintf(fout, "%.5lf\n", ans + now * sum);
    return 0;
}