#include <bits/stdc++.h>
#define eb emplace_back
using LL = long long;
static const int N = 4'005, M = 4'000;
int n, m, L, k;
LL ans;
LL s[N];
int u[N][N], d[N][N], l[N][N], r[N][N];
std::vector<int> del[N];
int lowbit(int x) { return x & -x; }
void add(int x, int v)
{
    for (; x <= M; x += lowbit(x))
        s[x] += v;
    return void();
}
int ask(int x)
{
    int ans = 0;
    for (; x; x -= lowbit(x))
        ans += s[x];
    return ans;
}
signed main()
{
    scanf("%d%d%d%d", &n, &m, &L, &k);
    for (int i = 1; i <= k; ++i)
    {
        static int x, y;
        scanf("%d%d", &x, &y);
        u[x][y] = d[x][y] = x;
        l[x][y] = r[x][y] = y;
    }
    for (int i = 1; i <= m; ++i)
        d[n + 1][i] = n + 1;
    for (int i = 1; i <= n; ++i)
        r[i][m + 1] = m + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            u[i][j] = u[i][j] ? u[i][j] : u[i - 1][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            l[i][j] = l[i][j] ? l[i][j] : l[i][j - 1];
    for (int i = n; i >= 1; --i)
        for (int j = m; j >= 1; --j)
            d[i][j] = d[i][j] ? d[i][j] : d[i + 1][j];
    for (int i = n; i >= 1; --i)
        for (int j = m; j >= 1; --j)
            r[i][j] = r[i][j] ? r[i][j] : r[i][j + 1];
    for (int i = 1 - m; i <= n - 1; ++i)
    {
        memset(s, 0, sizeof s);
        for (int j = 1; j <= n; ++j)
            del[j].clear();
        for (int j = 1; j <= n; ++j)
            if (j > i && j <= m + i)
            {
                add(j, 1);
                int dis = std::min(r[j][j - i] - j + i, d[j][j - i] - j);
                del[j + dis].eb(j);
                for (int p : del[j])
                    add(p, -1);
                int k = std::min(j - i - l[j][j - i], j - u[j][j - i]);
                if (k >= L)
                    ans += ask(j - L + 1) - ask(j - k);
            }
    }
    return printf("%lld\n", ans), 0;
}