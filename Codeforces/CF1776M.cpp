#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

#define eb emplace_back

static const int N = 100'005;

int n, in[N], dep[N], size[N];
bool flag, have[2];
std::vector<int> e[N];

void dfs(int x, int fa, int v)
{
    size[x] = (x >= v);
    if (x >= v)
        have[dep[x] % 2] = true;
    for (int y : e[x])
        if (y != fa)
        {
            dep[y] = dep[x] + 1;
            dfs(y, x, v);
            size[x] += size[y];
        }
    return void();
}

void dfs2(int x, int fa, int v)
{
    int cnt = 0;
    for (int y : e[x])
        if (y != fa)
        {
            dfs2(y, x, v);
            cnt += (size[y] != 0);
        }
    cnt += size[1] != size[x];
    if (cnt > 2 && have[dep[x] % 2])
        flag = true;
    return void();
}

bool check(int x)
{
    for (int i = 1; i <= n; ++i)
        if (in[i] == 1 && i >= x)
            return true;
    have[0] = have[1] = false;
    flag = false;
    dfs(1, 0, x);
    dfs2(1, 0, x);
    if (have[0] && have[1])
        return true;
    if (flag)
        return true;
    return false;
}

signed main()
{
    fin = stdin;
    fout = stdout;
    ferr = stderr;
    fscanf(fin, "%d", &n);
    for (int i = 1; i < n; ++i)
    {
        static int u, v;
        fscanf(fin, "%d%d", &u, &v);
        e[u].eb(v), e[v].eb(u);
        ++in[u], ++in[v];
    }
    if (n % 2 == 0)
        return fprintf(fout, "%d\n", n), 0;

    int l = 1, r = n, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    return fprintf(fout, "%d\n", ans), 0;
}