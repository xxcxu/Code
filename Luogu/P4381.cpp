#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e6 + 5;
int n, st, cnt, ans, ans1, ans2, ans3, edge_cnt = 1;
int f[N], s[N], dp[N], vis[N], vis2[N], ring[N], head[N];
struct Edge {
    int u, v, w, next;
    Edge(int u = 0, int v = 0, int w = 0, int next = 0):
        u(u), v(v), w(w), next(next) {}
} e[N << 1];
auto add(int x, int y, int z) -> void {
    e[++ edge_cnt] = Edge(x, y, z, head[x]);
    head[x] = edge_cnt;
}
auto Dfs(int x, int fa) -> bool {
    if (vis[x] == 1) {
        vis[x] = 2;
        ring[++ cnt] = x;
        vis2[x] = 1;
        return 1;
    }
    vis[x] = 1; 
    for (int i = head[x]; i; i = e[i].next) {
        const int &y = e[i].v, &z = e[i].w;
        if (y != fa && Dfs(y, x)) {
            if (vis[x] != 2) {
                ring[++ cnt] = x;
                vis2[x] = 1;
                s[cnt] = s[cnt - 1] + z;
            }
            else {
                s[st - 1] = s[st] - z;
                return 0;   
            }
            return 1;   
        }
    } return 0;
}
auto TreeDp(int x) -> void {
    vis2[x] = true;
    for (int i = head[x]; i; i = e[i].next) {
        const int &y = e[i].v, &z = e[i].w;
        if (vis2[y]) continue;
        TreeDp(y);
        ans1 = std::max(ans1, dp[x] + dp[y] + z);
        dp[x] = std::max(dp[x], dp[y] + z);
    }
}
auto solve(int x) -> void {
    st = cnt + 1;
    ans2 = ans3 = 0;
    Dfs(x, -1);
    for (int i = st; i <= cnt; ++i) {
        ans1 = 0;
        TreeDp(ring[i]);
        ans2 = std::max(ans2, ans1);
        f[i + cnt - st + 1] = f[i] = dp[ring[i]];
        s[i + cnt - st + 1] = s[i + cnt - st] + s[i] - s[i - 1];
    }
    std::deque<int> q;
    for (int i = st; i <= 2 * cnt - st + 1; ++i) {
        while (q.size() && q.front() <= i - cnt + st - 1)
            q.pop_front();
        if (q.size())
            ans3 = std::max(ans3, f[q.front()] + f[i] + s[i] - s[q.front()]);
        while (q.size() && f[q.back()] - s[q.back()] <= f[i] - s[i])
            q.pop_back();
        q.push_back(i);
    } ans += std::max(ans2, ans3);
}
auto main() -> decltype(0) {
    scanf("%lld", &n); 
    for (int i = 1, v, w; i <= n; ++i) {
        scanf("%lld%lld", &v, &w);
        add(i, v, w);
        add(v, i, w);
    }
    for (int i = 1; i <= n; ++i)
        if (!vis2[i])
            solve(i);
    return printf("%lld\n", ans), 0;
}