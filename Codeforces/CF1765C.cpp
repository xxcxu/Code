#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 2005, P = 998244353;

int n, k, ans;
int fac[N], ifac[N];
int f[2][N], g[2][N];

int inc(int x, int y) { return (x + y) % P; }
void cinc(int &x, int y) { x = inc(x, y); }
int dec(int x, int y) { return (x + P - y) % P; }
void cdec(int &x, int y) { x = dec(x, y); }
int mul(int x, int y) { return 1LL * x * y % P; }
void cmul(int &x, int y) { x = mul(x, y); }
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
    return void();
}
int binom(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return mul(fac[n], mul(ifac[n - m], ifac[m]));
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d%d", &n, &k);
    init(4 * n);
    for (int min = 0; min < n && 4 * min <= k; ++min)
    {
        std::memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int c = 0; c < 4; ++c)
        {
            std::memset(g, 0, sizeof g);
            for (int i = min; i <= n; ++i)
            {
                int coef = mul(ifac[i], ifac[n - i]);
                for (int s = 0; s < 2; ++s)
                    for (int sum = c * n; sum >= 0; --sum)
                        cinc(g[s | (i == min)][sum + i], mul(f[s][sum], coef));
            }
            std::memcpy(f, g, sizeof f);
        }
        for (int S = 0; S < 4 * n && S <= k; ++S)
        {
            int coef = 1;
            if (S == k)
                cmul(coef, n * 4 - S);
            cmul(coef, mul(fac[S], mul(fac[4 * n - S - 1], fac[n - min])));
            cmul(coef, ifac[n - min - 1]);
            cinc(ans, mul(coef, f[1][S]));
        }
    }
    int ways = mul(binom(n * 4, n), mul(binom(n * 3, n), binom(n * 2, n)));
    cmul(ans, inv(ways));
    return fprintf(fout, "%d\n", ans), 0;
}