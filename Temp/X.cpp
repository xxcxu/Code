#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5;
int n, K, X, T, ans, s[N], t[N], dis[N];
std::vector<int> e[N];
bool check(int S) {
    static std::queue<int> q; T = 0;
    for (int i = 1; i <= n; ++i) e[i].clear();
    for (int i = 1; i <= n; ++i) {
        if (i - 1 > 0) e[i].emplace_back(i - 1);
        if (i + 1 < n) e[i].emplace_back(i + 1);
    }
    for (int i = 1; i <= n; ++i) if (S >> (i - 1) & 1) t[++ T] = i;
    for (int i = 1; i <= K; ++i) {
        if (s[i - 1] > 0) e[s[i]].emplace_back(s[i - 1]);
        if (s[i + 1] < n) e[s[i]].emplace_back(s[i + 1]);
    }
    for (int i = 1; i <= T; ++i) {
        if (t[i - 1] > 0) e[t[i]].emplace_back(t[i - 1]);
        if (t[i + 1] < n) e[t[i]].emplace_back(t[i + 1]);
    }
    while (q.size()) q.pop();
    q.emplace(1);
    std::memset(dis, 0, (n + 1) * sizeof(int));
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : e[u]) 
            if (v != 1 && !dis[v]) dis[v] = dis[u] + 1, q.emplace(v);
    }
    for (int i = 1; i <= n; ++i) if (dis[i] > X) return false;
    return true;
}
signed main() {
    freopen("X.in", "r", stdin);
    freopen("X.out", "w", stdout);
    scanf("%d%d%d", &n, &K, &X); ++ n;
    for (int i = 1; i <= K; ++i) scanf("%d", s + i), ++ s[i];
    for (int i = 1; i < K; ++i) ans = mul(ans, f[s[i + 1] - s[i]][][]);
    printf("%d\n", ans);
    return 0;
}
// 私はずっと最低で見えないものも見えると言うの
// wa da si na ci do sa yi dei dei
// mi ye na yi mo no mo mi ye lu do yu no 