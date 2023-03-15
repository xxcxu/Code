#include <bits/stdc++.h>
using PII = std::pair<int, int>;
FILE *fin, *fout, *ferr;
#define ep emplace
#define eb emplace_back
static const int N = 100'005;
int n, m, k, ans, max;
int a[N], b[N], deg[N], vis[N];
std::vector<PII> e[N];
std::queue<int> q;
int backet[N * 40];
std::bitset<N * 40> dp;
void add(int x, int v)
{
    ans += v, a[m] += v;
    return void();
}
void dfs(int x, int fa, int rt)
{
    vis[x] = true;
    for (auto [y, z] : e[x])
    {
        if (y == fa)
            continue;
        if (y == rt)
        {
            add(x, z);
            return void();
        }
        if (vis[y])
            continue;
        add(x, z);
        return dfs(y, x, rt);
    }
}
void topsort()
{
    for (int i = 1; i <= n * 2; ++i)
        if (deg[i] == 1)
            q.ep(i);
    while (q.size())
    {
        int x = q.front();
        q.pop();
        vis[x] = true;
        for (auto [y, z] : e[x])
        {
            if (deg[y] == 1)
                continue;
            ans += z;
            if (--deg[y] == 1)
                q.ep(y);
        }
    }
}
signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r");
    // fout = fopen("Output.txt", "w+");
    // ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%d%d", &n, &k);
    for (int i = 1; i <= n * 2; ++i)
    {
        static int u, v, w;
        fscanf(fin, "%d%d%d", &u, &v, &w);
        v += n;
        ++deg[u], ++deg[v];
        e[u].eb(v, w), e[v].eb(u, -w);
    }
    for (int i = 1; i <= n * 2; ++i)
        if (deg[i] == 0)
            return fputs("NO\n", fout), 0;
    topsort();
    max = n * 40;
    for (int i = 1; i <= n * 2; ++i)
    {
        if (vis[i])
            continue;
        ++m;
        dfs(i, 0, i);
        a[m] *= -2;
        ++backet[a[m] + max];
    }
    std::sort(a + 1, a + m + 1);
    m = std::unique(a + 1, a + m + 1) - a - 1;
    int tot = 0;
    for (int i = 1; i <= m; ++i)
    {
        int p2 = 1, A = a[i] + max;
        while (backet[A] >= p2)
        {
            b[++tot] = a[i] * p2;
            backet[A] -= p2;
            p2 <<= 1;
        }
        if (backet[A])
            b[++tot] = a[i] * backet[A];
    }
    dp.set(ans + max);
    for (int i = 1; i <= tot; ++i)
        if (b[i] > 0)
            dp |= dp << b[i];
        else
            dp |= dp >> (-b[i]);
    for (int i = -k; i <= k; ++i)
        if (dp[i + max])
            return fputs("YES\n", fout), 0;
    return fputs("NO\n", fout), 0;
}