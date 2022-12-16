#include <bits/stdc++.h>
static constexpr int N = 1e6 + 5;
int n, rt, all, now, cnt, cut;
int mx[N], buc[N], size[N], ans[N];
std::vector<int> e[N];
void dfs(int x, int pre) {
    size[x] = 1;
    for (int y : e[x]) {
        if (y == pre) continue; dfs(y, x);
        size[x] += size[y];
        mx[x] = std::max(mx[x], size[y]);
    } mx[x] = std::max(mx[x], n - size[x]);
    if (mx[x] <= (n >> 1)) rt = x;
}
void solve(int x, int pre) {
    ans[x] = ans[pre];
    for (int y : e[x]) if (y ^ pre) solve(y, x);
    if (now + all - size[x] > (n >> 1)) ++ ans[x];
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs(1, 0); dfs(rt, 0);
    for (int y : e[rt]) ++ buc[size[y]];
    cut = (n >> 1), now = n, cnt = 1;
    for (; now > (n >> 1); -- cut)
        while (buc[cut] --) {
            now -= cut;
            if (now <= (n >> 1)) break;
            else ++ cnt;
        }
    ++ cut;
    for (int y : e[rt]) {
        all = size[y];
        if (size[y] >= cut) {
            ans[rt] = cnt - 1;
            solve(y, rt);
        } else {
            if (now + cut - size[y] <= (n >> 1)) {
                now += cut - size[y];
                ans[rt] = cnt - 1;
                solve(y, rt);
                now -= cut - size[y];
            } else {
                all = 0;
                ans[rt] = cnt;
                solve(y, rt);
            }
        }
    }
    ans[rt] = 0;
    for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
    return 0;
}