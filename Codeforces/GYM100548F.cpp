#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 1'000'005, P = 1'000'000'007;

int n, m, k;
int c[N];

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
int inv(int x) { return qpow(x, P - 2); }
void initCK(int n)
{
    c[0] = 1;
    for (int i = 1; i <= n; ++i)
        c[i] = mul(c[i - 1], mul(k - i + 1, inv(i)));
    return void();
}
int G(int x) { return mul(x, qpow(x - 1, n - 1)); }

void solve(int Case)
{
    fscanf(fin, "%d%d%d", &n, &m, &k);
    int coef = 0;
    initCK(k);
    for (int i = 1; i <= k; ++i)
        if (k - i & 1)
            coef = dec(coef, mul(c[i], G(i)));
        else
            coef = inc(coef, mul(c[i], G(i)));
    int res = 1;
    for (int i = 1; i <= k; ++i)
        res = mul(res, m - i + 1);
    for (int i = 1; i <= k; ++i)
        res = mul(res, inv(i));
    return fprintf(fout, "Case #%d: %d\n", Case, mul(res, coef)), void();
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    int t, Case = 0;
    fscanf(fin, "%d", &t);
    while (t--)
        solve(++Case);
    return 0;
}