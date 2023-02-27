#include <bits/stdc++.h>
#define int long long
#define eb emplace_back
using pii = std::pair<int, int>;
static const int N = 3005;
int n, m;
int in[N], dis[N], pre[N];
bool vis[N];
std::vector<pii> e[N];
std::vector<int> g[N];
void dijkstra() {
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    std::memset(dis, 0x3f, sizeof dis);
    std::memset(vis, 0, sizeof vis);
    q.emplace(dis[1] = pre[1] = 0, 1);
    while (q.size()) {
        int x = q.top().second; q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        dis[x] = std::max(dis[x], pre[x]);
        for (int y : g[x]) {
            pre[y] = std::max(pre[y], dis[x]);
            -- in[y];
            if (!in[y]) q.emplace(std::max(pre[y], dis[y]), y); 
        }
        for (pii t : e[x]) {
            int y = t.first, z = t.second;
            if (dis[y] > dis[x] + z) {
                dis[y] = dis[x] + z;
                if (!in[y]) q.emplace(std::max(pre[y], dis[y]), y);
            }
        }
    }
}
signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; ++i) {
        static int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        e[u].eb(v, w);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", in + i);
        for (int j = 1; j <= in[i]; ++j) {
            static int x;
            scanf("%lld", &x);
            g[x].eb(i);
        }
    }
    dijkstra();
    printf("%lld\n", dis[n]);
    return 0;
}