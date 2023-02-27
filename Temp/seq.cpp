#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 100'005, P = 1'000'000'007;

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }

int n, m, ans;
int a[N];

int qpow(int x, int y)
{
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1)
            ans = mul(ans, x);
    return ans;
}

void dfs(int x, int s1, int s2, int n)
{
    if (x == m)
    {
        ans = std::max(ans, s2);
        return void();
    }
    dfs(x + 1, mul(s1, 2), inc(mul(n, s1), mul(s2, 2)), mul(n, 2));
}

signed main()
{
    // fin = stdin;
    // fout = stdout;
    // ferr = stderr;
    fin = fopen("seq.in", "r");
    fout = fopen("seq.out", "w+");
    ferr = fopen("seq.out", "w+");
    fscanf(fin, "%d%d", &n, &m);
    int sum = 0, sum2 = 0;
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", a + i);
    for (int i = 1; i <= n; ++i)
        sum = inc(sum, a[i]), sum2 = inc(sum2, sum);

    dfs(0, sum, sum2, n);

    n = mul(qpow(2, m - 1), n);
    sum = mul(qpow(2, m - 1), sum);
    ans = std::max(ans, mul(inc(mul(n, 2), 1), sum));

    fprintf(fout, "%d\n", ans);
    return 0;
}