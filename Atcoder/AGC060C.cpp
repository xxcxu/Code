#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 5005, P = 998'244'353;

int n, a, b;
int size[N];
int f[N][N];

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
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d%d%d", &n, &a, &b);
    a = n - a;
    b = n - b;
    for (int i = 1; i <= n; ++i)
        size[i] = inc(mul(size[i - 1], 2), 1);
    for (int i = 1; i <= n; ++i)
        f[a - 1][i] = 1;
    for (int i = a; i < n; ++i)
        for (int j = b; j < n; ++j)
        {
            int coef = mul(size[i], qpow(inc(size[i], size[j]), P - 2));
            f[i][j] = inc(mul(coef, f[i - 1][j]), mul(dec(1, coef), f[i][j - 1]));
        }
    fprintf(fout, "%d\n", f[n - 1][n - 1]);
    return 0;
}