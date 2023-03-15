#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 500'005, P = 998'244'353;

int n, a[N];

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

void solve()
{
    fscanf(fin, "%d", &n);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", a + i);
    return fprintf(fout, "%d\n", n == 1 ? 1 : qpow(n, n - 2)), void();
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("camphor.in", "r");
    fout = fopen("camphor.out", "w+");
    int t;
    fscanf(fin, "%d", &t);
    while (t--)
        solve();
    return 0;
}