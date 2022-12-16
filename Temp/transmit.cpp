#include <bits/stdc++.h>
using ll = long long;
#define eb emplace_back
static constexpr int N = 2e5 + 5, M = N << 2;
static constexpr ll inf = 1e18;
int n, q, K;
ll v[N], tr[M];
int fa[N], dep[N], dfn[N], red[N], top[N], size[N], son[N];
std::vector<int> e[N];
#define ls (x << 1)
#define rs (x << 1 | 1)
void pushup(int x) {tr[x] = tr[ls] + tr[rs];}
void build(int x, int l, int r) {
    if (l == r) return tr[x] = v[red[l]], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid); build(rs, mid + 1, r);
    pushup(x);
}
ll query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tr[x];
    int mid = (l + r) >> 1; ll ans = 0;
    if (ql <= mid) ans += query(ls, l, mid, ql, qr);
    if (qr > mid) ans += query(rs, mid + 1, r, ql, qr);
    return ans;
}
ll qRange(int x, int y) {
    ll ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
        ans += query(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) std::swap(x, y);
    ans += query(1, 1, n, dfn[x], dfn[y]);
    return ans;
}
void dfs1(int x, int pre) {
    static int time_stamp = 0;
    size[x] = 1; fa[x] = pre;
    dep[x] = dep[pre] + 1;
    dfn[x] = ++ time_stamp;
    red[dfn[x]] = x;
    for (int y : e[x]) if (y != pre) {
        dfs1(y, x);
        size[x] += size[y];
        if (size[y] > size[son[x]]) son[x] = y;
    }
}
void dfs2(int x, int tp) {
    top[x] = tp;
    if (son[x]) dfs2(son[x], tp);
    for (int y : e[x]) if (y != son[x] && y != fa[x]) dfs2(y, y);
}
signed main() {
	scanf("%d%d%d", &n, &q, &K);
	for (int i = 1; i <= n; ++i) scanf("%lld", v + i);
	for (int i = 1; i < n; ++i) {
		static int u, v;
		scanf("%d%d", &u, &v);
		e[u].eb(v); e[v].eb(u);
	}
	dfs1(1, 0); dfs2(1, 1); build(1, 1, n);
	while (q--) {   
		static int s, t;
        if (K == 1) {
            scanf("%d%d", &s, &t);
            printf("%lld\n", qRange(s, t));
        }
	}
}