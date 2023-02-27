#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 305;
int n, P;
int d[N], Pi[N], pow2[N], dp[N][N];

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }

int qpow(int x, int y)
{
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1)
            ans = mul(ans, x);
    return ans;
}

signed main()
{
    fin = fopen("interval.in", "r");
    fout = fopen("interval.out", "w+");
    ferr = fopen("interval.out", "w+");
    fscanf(fin, "%d%d", &n, &P);
    for (int i = 0; i <= n; ++i)
        Pi[i] = i * (i + 1) / 2;
    for (int i = 0; i <= n; ++i)
        pow2[i] = qpow(2, Pi[i]);

    dp[0][0] = 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j)
        {
            dp[i + 1][j + 1] = inc(dp[i + 1][j + 1], dp[i][j]);
            for (int k = i + 2; k <= n; ++k)
                dp[k][j + 1] = inc(dp[k][j + 1], mul(dp[i][j], pow2[k - i - 2]));
        }
    for (int i = 0; i <= n; ++i)
    {
        d[i] = pow2[i];
        for (int j = 0; j < i; ++j)
            d[i] = dec(d[i], mul(dp[i][j], d[j]));
    }
    fprintf(fout, "%d\n", d[n]);
    return 0;
}