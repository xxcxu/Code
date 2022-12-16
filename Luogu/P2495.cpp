#include <bits/stdc++.h>
#define int long long
static constexpr int N = 25e4 + 5;
int n, m, cnt, head[N], inT[N], outT[N], min[N], dep[N], sum[N], tree[N << 2], anc[N][25];
std::stack<int> s; bool special[N];
struct Edge {int to, link, next;} e[N << 1];
void Add(int u, int v, int w) {e[++ cnt] = {v, w, head[u]}; head[u] = cnt;}
void Dfs(int x) {
    static int time_stamp = 0;
    inT[x] = ++ time_stamp;
    for (int i = 1; i < 25; ++i) anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (int i = head[x]; i; i = e[i].next)
        if (!inT[e[i].to]) {
            dep[e[i].to] = dep[x] + 1;
            anc[e[i].to][0] = x;
            min[e[i].to] = std::min(min[x], e[i].link);
            Dfs(e[i].to);
        } outT[x] = ++ time_stamp;
}
int Lca(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = 24; ~i; --i) if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (int i = 24; ~i; --i) if (anc[x][i] ^ anc[y][i]) x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1, u, v, w; i < n; ++i) {
        scanf("%lld%lld%lld", &u, &v, &w);
        Add(u, v, w); Add(v, u, w);
    } min[1] = 0x7f7f7f7f; dep[1] = 1; Dfs(1); scanf("%lld", &m);
    for (int i = 1; i <= m; ++i) {
        int k; scanf("%lld", &k);
        for (int j = 1; j <= k; ++j)
            scanf("%lld", tree + j), special[tree[j]] = true, sum[tree[j]] = min[tree[j]];
        std::sort(tree + 1, tree + k + 1, [&](int a, int b) {
            int x = (a > 0 ? inT[a] : outT[-a]);
            int y = (b > 0 ? inT[b] : outT[-b]);
            return x < y;
        });
        for (int j = 1; j < k; ++j) {
            int lca = Lca(tree[j], tree[j + 1]);
            if (!special[lca]) tree[++ k] = lca, special[lca] = true;
        }
        int k2 = k; for (int j = 1; j <= k2; ++j) tree[++ k] = - tree[j];
        if (!special[1]) tree[++ k] = 1, tree[++ k] = -1;
        std::sort(tree + 1, tree + k + 1, [&](int a, int b) {
            int x = (a > 0 ? inT[a] : outT[-a]);
            int y = (b > 0 ? inT[b] : outT[-b]);
            return x < y;
        });
        for (int j = 1; j <= k; ++j) {
            if (tree[j] > 0) s.push(tree[j]);
            else {
                int x = s.top(); s.pop();
                if (x ^ 1) sum[s.top()] += std::min(sum[x], min[x]);
                else printf("%lld\n", sum[1]);
                sum[x] = 0; special[x] = false;
            }
        }
    } return 0;
}