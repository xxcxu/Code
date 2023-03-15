#include <bits/stdc++.h>

#define int long long

#define ep emplace
#define eb emplace_back

FILE *fin, *fout, *ferr;

static const int N = 1'000'005, inf = 1'000'000'000;

int n, m, root;
int d[N], p[N], dp[N];
std::vector<int> e[N];

void dfs(int x)
{
    int max = 0;
    for (int y : e[x])
    {
        dfs(y);
        dp[x] += dp[y];
        max = std::max(max, dp[y]);
    }
    dp[x] -= max;
    return void();
}

void build()
{
    std::queue<int> q;
    int cnt = n;
    for (int i = 1; i <= n; ++i)
        q.ep(i);
    while (q.size() > 1)
    {
        ++cnt;
        for (int i = 1; i <= 3; ++i)
            e[cnt].eb(q.front()), q.pop();
        q.ep(cnt);
    }
    root = q.front();
    return void();
}
int calc(int a, int b, int n, int m, int L)
{
    memset(c, 0, sizeof c);
    ll res = 0;
    if (min(n - a + 1, m - b + 1) < L)
        return 0;
    int cnt = 0;
    for (int i = a + L - 1, j = b + L - 1; i <= n && j <= m; ++i, ++j)
        add(i - l[i][j] + 1, 1), ++cnt;
    for (int i = a, j = b; i <= n && j <= m; ++i, ++j)
        d[i][j] = d[i - 1][j - 1] + 1;
    for (int i = a, j = b; i <= n && j <= m; ++i, ++j)
    {
        if (r[i][j] >= L)
        {
            res += ask(i);
            p[d[i + r[i][j] - L][j + r[i][j] - L]].emplace_back(i);
        }
        add(i + L - l[i + L - 1][j + L - 1], -1), --cnt;
        for (int x : p[d[i][j]])
            res -= ask(x);
        p[d[i][j]].clear();
    }
    return res;
}

bool check(int x)
{
    std::memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; ++i)
        dp[i] = 1;
    for (int i = 1; i <= m; ++i)
        dp[p[i]] = (d[i] < x ? inf : 0);
    int sum = 0;
    for (int i = m + 1; i <= n; ++i)
        sum += d[i] >= x;
    dfs(root);
    return dp[root] <= sum;
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%lld%lld", &n, &m);
    for (int i = 1; i <= m; ++i)
        fscanf(fin, "%lld%lld", d + i, p + i);
    for (int i = m + 1; i <= n; ++i)
        fscanf(fin, "%lld", d + i);
    build();
    int l = 1, r = 1'000'000'000, ans = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    fprintf(fout, "%lld\n", ans);
    return 0;
}