#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 85;

int n, m, P, ans;
int a[N][N], b[N][N], c[N][N];
int pow2[N], fac[N], ifac[N];

int inc(int x, int y) { return (x + y) % P; }
template <typename... Args>
int inc(int x, Args... args) { return inc(x, inc(args...)); }
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
void init(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = mul(fac[i - 1], i);
    ifac[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; --i)
        ifac[i] = mul(ifac[i + 1], i + 1);
    pow2[0] = 1;
    for (int i = 1; i <= n; ++i)
        pow2[i] = mul(pow2[i - 1], 2);
    return void();
}
int down(int x, int p)
{
    int ans = 1;
    for (int i = 1; i <= p; ++i)
        ans = mul(ans, inc(dec(x, i), 1));
    return ans;
}
int binom(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return mul(fac[n], ifac[m], ifac[n - m]);
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d%d%d", &n, &m, &P);

    init(N - 1);

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k <= j; ++k)
                if ((j - k) & 1)
                    a[i][j] = dec(a[i][j], mul(binom(j, k), qpow(pow2[k], i)));
                else
                    a[i][j] = inc(a[i][j], mul(binom(j, k), qpow(pow2[k], i)));

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k <= j; ++k)
                if ((j - k) & 1)
                    b[i][j] = dec(b[i][j], mul(binom(j, k), down(dec(pow2[k], 1), i)));
                else
                    b[i][j] = inc(b[i][j], mul(binom(j, k), down(dec(pow2[k], 1), i)));

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k < i; ++k)
                for (int l = 0; l < j; ++l)
                    if (!(n & 1 && i == n && k == n - 1))
                        c[i][j] = inc(c[i][j], mul(binom(i, k), binom(j, l), dec(a[k][l], c[k][l]), qpow(pow2[l], i - k), b[i - k][j - l]));

    for (int i = 0; i <= m; ++i)
        ans = inc(ans, mul(binom(m, i), dec(a[n][i], c[n][i])));
    return fprintf(fout, "%d\n", ans), 0;
}