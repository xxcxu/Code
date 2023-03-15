#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 105;

int n, m, K, P;
int c[N][N];
int dp[N][N][N];

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }
template <typename... Args>
int mul(int x, Args... args) { return mul(x, mul(args...)); }

int dfs(int i, int j, int k)
{
    if (i + 1 < k * 2 || i < k)
        return 0;
    if (j < 1 && k > 0)
        return 0;
    if (j == 1 && k > 1)
        return 0;
    if (i == 0)
        return k == 0;
    if (dp[i][j][k] != -1)
        return dp[i][j][k];
    dp[i][j][k] = 0;
    for (int p = 1; p <= i; ++p)
        if (c[i - 1][p - 1])
            for (int t = 0; t <= k - (j == 1); ++t)
                dp[i][j][k] = inc(dp[i][j][k], mul(c[i - 1][p - 1], dfs(p - 1, j - 1, t), dfs(i - p, j - 1, k - t - (j == 1))));
    return dp[i][j][k];
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d%d%d%d", &n, &m, &K, &P);
    std::memset(dp, -1, sizeof dp);
    c[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = inc(c[i - 1][j], c[i - 1][j - 1]);
    }
    fprintf(fout, "%d\n", dfs(n, m, K));
    return 0;
}