#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll a[100005];
vector<pair<int, ll>> edge[100005];
ll T, dp[100005][2];
void dfs(int x, int f)
{
    dp[x][0] = dp[x][1] = 0;
    for (auto e : edge[x])
        if (e.first != f)
        {
            int y = e.first;
            ll z = e.second;
            dfs(y, x);
            ll g[2] = {0x3f3f3f3f3f3f3f3f, 0x3f3f3f3f3f3f3f3f};
            if (dp[x][0] + dp[y][0] + max(0ll, z - a[y]) <= T)
                g[0] = min(g[0], max(dp[x][0], dp[y][0] + max(0ll, z - a[y])));
            if (dp[x][1] + dp[y][0] + max(0ll, z - a[y]) <= T)
                g[1] = min(g[1], max(dp[x][1], dp[y][0] + max(0ll, z - a[y])));
            if (dp[x][0] + dp[y][0] + max(0ll, z - a[y] - a[x]) <= T)
                g[1] = min(g[1], max(dp[x][0], dp[y][0] + max(0ll, z - a[y] - a[x])));
            if (dp[x][0] + dp[y][1] + z <= T)
                g[0] = min(g[0], max(dp[x][0], dp[y][1] + z));
            if (dp[x][1] + dp[y][1] + z <= T)
                g[1] = min(g[1], max(dp[x][1], dp[y][1] + z));
            if (dp[x][0] + dp[y][1] + max(0ll, z - a[x]) <= T)
                g[1] = min(g[1], max(dp[x][0], dp[y][1] + max(0ll, z - a[x])));
            dp[x][0] = g[0], dp[x][1] = g[1];
        }
}
int main()
{
    freopen("length.in", "r", stdin);
    freopen("length.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (int i = 1; i < n; i++)
    {
        int x, y;
        ll z;
        scanf("%d%d%lld", &x, &y, &z);
        edge[x].push_back(make_pair(y, z));
        edge[y].push_back(make_pair(x, z));
    }
    ll l = 0, r = 20000000000ll;
    while (l < r)
    {
        ll mid = l + r >> 1;
        T = mid;
        dfs(1, 0);
        if (dp[1][1] < 0x3f3f3f3f3f3f3f3f)
            r = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", l);
    return 0;
}