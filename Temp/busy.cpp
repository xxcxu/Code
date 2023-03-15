#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int KK = 25, N2 = 1 << 17, P = 998244353;
int n, p, K, x0;
int c[N2], sum1[N2], sum2[N2];
int dp[KK][N2];

int count(int x)
{
    int res = 0;
    for (; x; x -= x & -x)
        ++res;
    return res;
}

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }
template <typename... Args>
int mul(int x, Args... args) { return mul(x, mul(args...)); }
int qpow(int x, int y)
{
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1)
            ans = mul(ans, x);
    return ans;
}
int inv(int x) { return qpow(x, P - 2); }

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("busy.in", "r"), fout = fopen("busy.out", "w+");
    fscanf(fin, "%d%d%d%d", &n, &p, &K, &x0);
    int R = (1 << n) - 1;
    for (int i = 0; i <= R; ++i)
        fscanf(fin, "%d", c + i);
    if (n == 1)
    {
        for (int i = 0; i <= R; ++i)
        {
            if (i == 0)
                fprintf(fout, "%d ", mul(dec(1, qpow(p, K)), c[0], K));
            else if (i == x0)
                fprintf(fout, "%d ", mul(qpow(p, K), c[0], K));
            else
                fprintf(fout, "%d ", 0);
        }
        return 0;
    }
    dp[0][x0] = 1;
    for (int i = 0; i <= R; ++i)
    {
        for (int j = i; j; j = (j - 1) & i)
            sum1[i] = inc(sum1[i], c[j]);
        for (int j = i ^ R; j; j = (j - 1) & (i ^ R))
            sum2[i] = inc(sum2[i], c[j ^ i]);
    }
    for (int i = 1; i <= K; ++i)
    {
        for (int j = 0; j <= R; ++j)
        {
            for (int s = j;; s = (s - 1) & j)
            {
                if (i == 0 && s != x0)
                    continue;
                int lj = count(j), ls = count(s);
                int coef_or = mul(p, qpow(2, ls), inv(qpow(2, n)));
                dp[i][j] = inc(dp[i][j], mul(dp[i - 1][s], coef_or));
                if (s == 0)
                    break;
            }
            for (int S = R ^ j;; S = (S - 1) & (R ^ j))
            {
                int s = S ^ j;
                if (i == 0 && s != x0)
                    continue;
                int lj = count(j), ls = count(s);
                int coef_and = mul(dec(1, p), qpow(2, n - ls), inv(qpow(2, n)));
                dp[i][j] = inc(dp[i][j], mul(dp[i - 1][s], coef_and));
                if (S == 0)
                    break;
            }
        }
    }
    for (int i = 0; i <= R; ++i)
        fprintf(fout, "%d ", mul(dp[K][i], K));
    return 0;
}