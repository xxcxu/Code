#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 205, K = 1'005, P = 1'000'000'007;

int n, k;
int a[N], d[N], dp[N][N][K];

int inc(int x, int y) { return (x + y) % P; }   
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r"), fout = fopen("output.out", "w+"), ferr = fopen("debug.out", "w+");
    fscanf(fin, "%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", a + i);
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i < n; ++i)
        d[i] = a[i + 1] - a[i];
    dp[0][0][0] = dp[0][1][0] = 1;
    for (int i = 1; i < n; ++i)
        for (int j = 0; j <= n; ++j)
            for (int l = 0; l <= k; ++l)
            {
                if (j > 0 && l >= j * d[i])
                    dp[i][j][l] = inc(dp[i][j][l], mul(j, dp[i - 1][j][l - j * d[i]]));
                if (j < n && l >= (j + 1) * d[i])
                    dp[i][j][l] = inc(dp[i][j][l], mul(j + 1, dp[i - 1][j + 1][l - (j + 1) * d[i]]));
                if (j > 0 && l >= (j - 1) * d[i])
                    dp[i][j][l] = inc(dp[i][j][l], dp[i - 1][j - 1][l - (j - 1) * d[i]]);
                if (j >= 0 && l >= j * d[i])
                    dp[i][j][l] = inc(dp[i][j][l], dp[i - 1][j][l - j * d[i]]);
            }
    int ans = 0;
    for (int i = 0; i <= k; ++i)
        ans = inc(ans, dp[n - 1][0][i]);
    return fprintf(fout, "%d\n", ans), 0;
}