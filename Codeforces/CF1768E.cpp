#include <bits/stdc++.h>

static const int N = 3'000'005;

FILE *fin, *fout, *ferr;
int n, P;
int fac[N], inv[N];

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
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = mul(inv[i + 1], i + 1);
    return void();
}
int binom(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return mul(fac[n], mul(inv[m], inv[n - m]));
}

int solve0()
{
    return 1;
}
int solve1()
{
    return dec(mul(2, dec(fac[2 * n], 1)), dec(fac[n], 1));
}
int solve2()
{
    int t2 = mul(2, mul(binom(2 * n, n), mul(fac[n], fac[2 * n])));
    for (int i = 0; i <= n; ++i)
    {
        int res = mul(binom(n, i), mul(binom(n, n - i), mul(binom(2 * n - i, n), mul(fac[n], mul(fac[n], fac[n])))));
        t2 = dec(t2, res);
    }
    t2 = dec(t2, solve0());
    t2 = dec(t2, solve1());
    return t2;
}
int solve3()
{
    return dec(fac[3 * n], inc(solve0(), inc(solve1(), solve2())));
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%d%d", &n, &P);
    init(N - 1);
    int ans = 0;
    ans = inc(ans, mul(solve0(), 0));
    ans = inc(ans, mul(solve1(), 1));
    ans = inc(ans, mul(solve2(), 2));
    ans = inc(ans, mul(solve3(), 3));
    fprintf(fout, "%d\n", ans);
    return 0;
}