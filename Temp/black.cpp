#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

#define eb emplace_back
#define all(x) x.begin(), x.end()

static const int N = 1'000'005, P = 998'244'353;

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

int n;
int fac[N], ifac[N], size[N];
int f[N], g[N], h[N];
std::vector<int> e[N];

void init(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = mul(fac[i - 1], i);
    ifac[n] = inv(fac[n]);
    for (int i = n - 1; i >= 1; --i)
        ifac[i] = mul(ifac[i + 1], i + 1);
    return void();
}

void dfs(int x, int fa)
{
    size[x] = 1;
    for (int y : e[x])
        if (y != fa)
        {
            dfs(y, x);
            size[x] = inc(size[x], size[y]);
            f[x] = inc(f[x], f[y]);
        }
    f[x] = inc(f[x], g[size[x]]);
    return void();
}

void dfs2(int x, int fa)
{
    for (int y : e[x])
        if (y != fa)
        {
            h[y] = dec(inc(h[x], g[n - size[y]]), g[size[y]]);
            dfs2(y, x);
        }
    return void();
}

signed main()
{
    fin = fopen("black.in", "r");
    fout = fopen("black.out", "w+");
    ferr = stderr;
    init(N - 1);
    fscanf(fin, "%d", &n);
    for (int i = 1; i < n; ++i)
    {
        static int u, v;
        fscanf(fin, "%d%d", &u, &v);
        e[u].eb(v), e[v].eb(u);
    }
    for (int i = 1; i < n; ++i)
        g[i] = mul(mul(i, inv(i + 1)), fac[n]);
    g[n] = mul(n - 1, fac[n - 1]);
    dfs(1, 0);
    h[1] = f[1];
    dfs2(1, 0);
    for (int i = 1; i <= n; ++i)
        fprintf(fout, "%d\n", h[i]);
    return 0;
}