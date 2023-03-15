#include <bits/stdc++.h>

using PII = std::pair<int, int>;

FILE *fin, *fout, *ferr;

#define eb emplace_back
static const int N = 200'005, inf = 0x3f3f3f3f;

int n;
int l[N], r[N], tr[N << 2], dfn[N], dp[N];
std::vector<PII> e[N];
std::vector<int> ans;

#define ls (x << 1)
#define rs (x << 1 | 1)

void pushup(int x)
{
    tr[x] = std::min(tr[ls], tr[rs]);
}

void build(int x, int l, int r)
{
    if (l == r)
    {
        tr[x] = dfn[l];
        return void();
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    return pushup(x);
}

int query(int x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return tr[x];
    int mid = (l + r) >> 1;
    int ans = inf;
    if (ql <= mid)
        ans = std::min(ans, query(ls, l, mid, ql, qr));
    if (qr > mid)
        ans = std::min(ans, query(rs, mid + 1, r, ql, qr));
    return ans;
}

void dfs(int x, int fa)
{
    static int time_stamp = 0;
    l[x] = ++time_stamp;
    dfn[time_stamp] = x;
    for (auto [y, z] : e[x])
    {
        if (y == fa)
            continue;
        dfs(y, x);
        if (z == 2 && !dp[y])
            dp[x] += 1;
        dp[x] += dp[y];
    }
    r[x] = time_stamp;
}

void dfs2(int x, int fa)
{
    if (!dp[x])
        return void();
    for (auto [y, z] : e[x])
    {
        if (y == fa)
            continue;
        if (!dp[y] && z == 2)
        {
            ans.eb(query(1, 1, n, l[y], r[y]));
            continue;
        }
        dfs2(y, x); 
    }
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%d", &n);
    for (int i = 1; i < n; ++i)
    {
        static int u, v, w;
        fscanf(fin, "%d%d%d", &u, &v, &w);
        e[u].eb(v, w);
        e[v].eb(u, w);
    }
    dfs(1, 0);
    fprintf(fout, "%d\n", dp[1]);
    build(1, 1, n);
    dfs2(1, 0);
    std::sort(ans.begin(), ans.end());
    for (int i = 0; i < dp[1]; ++i)
        fprintf(fout, "%d ", ans[i]);
    return fputs("\n", fout), 0;
}