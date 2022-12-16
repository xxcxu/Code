#include <bits/stdc++.h>
using pii = std::pair<int, int>;
static constexpr int N = 12e3 + 5;
int n, m, f[N], l[N], r[N], bel[N];
std::vector<pii> p;
std::stack<int> s[N];
void dfs(int x, int y) {
    if (x + 1 == y) {
        if ((int)s[x].size() == 1) s[y].emplace(s[x].top()), s[x].pop(), p.emplace_back(x, 1);
        else {
            int u = s[x].top(); s[x].pop();
            int v = s[x].top(); s[x].pop();
            if (u < v) p.emplace_back(x, 2), s[y].emplace(v), s[y].emplace(u);
            else p.emplace_back(x, 1), p.emplace_back(x, 1), s[y].emplace(u), s[y].emplace(v);
        }
        return void();
    }   
    int pos = l[x];
    for (int i = x + 1; i <= y; ++i) {
        l[i] = pos, r[i] = std::min(r[x], l[i] + f[y - i + 1] - 1);
        pos = r[i] + 1;
        for (int j = l[i]; j <= r[i]; ++j) bel[j] = i;
    }
    while ((int)s[x].size()) {
        int u = s[x].top(); s[x].pop();
        for (int i = x; i < bel[u]; ++i) p.emplace_back(i, 1);
        s[bel[u]].emplace(u);
    }
    for (int i = y - 1; i > x; --i)
        if (l[i] <= r[i]) dfs(i, y);
}

signed main() {
    freopen("hanoi.in", "r", stdin);
    freopen("hanoi.out", "w", stdout);
    scanf("%d%d", &n, &m);
    // f[1] = 1, f  [2] = 2, f[3] = 3;    /
    for (int i = 4; i <= m; ++i) f[i] = f[i - 1] * 2;
    for (int i = 1, x; i <= n; ++i) scanf("%d", &x), s[1].emplace(x);
    l[1] = 1, r[1] = n;
    dfs(1, m);
    printf("%d\n", (int)p.size());
    for (auto it : p) printf("%d %d\n", it.first, it.second);
    return 0;
}