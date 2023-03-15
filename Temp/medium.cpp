#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;
static const int N = 205, P = 1'000'000'007;
int n, m, v;
int a[N], sum[N];
int f[N][N * N];

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
    fscanf(fin, "%d%d%d", &n, &m, &v);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", a + i);
    std::sort(a + 1, a + n + 1);
    int ans = n, sum = n * 200;
    for (int i = 1; i <= n; ++i)
    {
        std::memset(f, 0, sizeof f);
        f[i][0] = 1;
        for (int j = i + 1; j <= n && a[j] - a[i] <= m; ++j)
            for (int k = 0; k <= sum; ++k)
                if (f[j - 1][k])
                {
                    f[j][k + a[j] - a[i]] = inc(f[j][k + a[j] - a[i]], f[j - 1][k]);
                    f[j][k] = inc(f[j][k], f[j - 1][k]);
                    if (k + a[j] - a[i] <= m * (n - v))
                        ans = inc(ans, f[j - 1][k]);
                }
    }
    std::reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::memset(f, 0, sizeof f);
        f[i][0] = 1;
        for (int j = i + 1; j <= n && a[i] - a[j] <= m; ++j)
            for (int k = 0; k <= sum; ++k)
                if (f[j - 1][k])
                {
                    f[j][k + a[i] - a[j]] = inc(f[j][k + a[i] - a[j]], f[j - 1][k]);
                    f[j][k] = inc(f[j][k], f[j - 1][k]);
                    if (k + a[i] - a[j] <= m * v)
                        ans = inc(ans, f[j - 1][k]);
                }
    }
    
    for (int i = 1; i <= n; ++i)
    {
        int pow2 = 1;
        for (int j = i + 1; j <= n && a[i] - a[j] <= m; ++j, pow2 = mul(pow2, 2))
            ans = dec(ans, pow2);
    }
    fprintf(fout, "%d\n", ans);
    return void();
}
signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("medium.in", "r");
    fout = fopen("medium.out", "w+");
    int t;
    fscanf(fin, "%d", &t);
    while (t--)
        solve();
    return 0;
}