#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 205, P = 998'244'353;

int n, m;
int a[N], fac[N];
int p[N][N];
int dp[N][N][N][2][2];

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }
void init(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = mul(fac[i - 1], i);
    return void();
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d", &n);
    init(n);
    ++n;
    for (int i = 0; i <= n; i++)
        p[i][n] = p[n][i] = p[0][i] = p[i][0] = -1;
    for (int i = 1; i < n; ++i)
    {
        fscanf(fin, "%d", a + i);
        if (!~a[i])
        {
            ++m;
            continue;
        }
        for (int j = 1; j <= n; ++j)
            p[i][j] = -1;
        for (int j = 1; j <= n; ++j)
            p[j][a[i]] = -1;
        p[i][a[i]] = 1;
    }
    dp[0][0][0][0][0] = 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k <= m; ++k)
                for (int r = 0; r < 2; ++r)
                    for (int c = 0; c < 2; ++c)
                    {
                        dp[i][j + 1][k][r][0] = inc(dp[i][j + 1][k][r][0], dp[i][j][k][r][c]);
                        dp[i + 1][j][k][0][c] = inc(dp[i + 1][j][k][0][c], dp[i][j][k][r][c]);
                        if (!r && p[i][j + 1] != -1)
                            dp[i][j + 1][k + (1 - p[i][j + 1])][1][1] = dec(dp[i][j + 1][k + (1 - p[i][j + 1])][1][1], dp[i][j][k][r][c]);
                        if (!c && p[i + 1][j] != -1)
                            dp[i + 1][j][k + (1 - p[i + 1][j])][1][1] = dec(dp[i + 1][j][k + (1 - p[i + 1][j])][1][1], dp[i][j][k][r][c]);
                    }
    int ans = 0;
    for (int i = 0; i <= m; ++i)
        ans = inc(ans, mul(dp[n][n][i][0][0], fac[m - i]));
    return fprintf(fout, "%d\n", ans), 0;
}