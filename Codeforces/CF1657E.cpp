#include <bits/stdc++.h>

static const int N = 505, P = 998'244'353;

FILE *fin, *fout, *ferr;

int n, m;
int c[N][N], dp[N][N];

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
void init(int n)
{
    c[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = inc(c[i - 1][j], c[i - 1][j - 1]);
    }
    return void();
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d%d", &n, &m);
    init(n + m);
    dp[0][0] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k <= j; ++k)
                dp[i][j] = inc(dp[i][j], mul(dp[i - 1][j - k], mul(c[n - 1 - j + k][k], qpow(m - i + 1, (j * 2 - k - 1) * k / 2 % (P - 1)))));
    fprintf(fout, "%d\n", dp[m][n - 1]);
    return 0;
}