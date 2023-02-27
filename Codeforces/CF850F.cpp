#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 100'005, P = 1'000'000'007;

int n, m, s, ans;
int a[N], f[N], g[N];

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
int frac(int x, int y) { return mul(x, qpow(y, P - 2)); }
signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d", &n);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", a + i);
    for (int i = 1; i <= n; ++i)
        m = std::max(m, a[i]), s = inc(s, a[i]);
    g[0] = frac(mul(dec(s, 1), dec(s, 1)), s);9
    for (int i = 1; i < m; ++i)
        g[i] = dec(g[i - 1], frac(s - 1, s - i));
    for (int i = 1; i <= m; ++i)
        f[i] = inc(f[i - 1], g[i - 1]);
    for (int i = 1; i <= n; ++i)
        ans = inc(ans, f[a[i]]);
    fprintf(fout, "%d\n", ans);
    return 0;
}