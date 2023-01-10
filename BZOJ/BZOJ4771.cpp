#include <bits/stdc++.h>
#define eb emplace_back
static const int N = 100005;
int n, q, id, cnt, lastans, maxdep, time_stamp;
int l[N], r[N], col[N], dep[N], ver[N], anc[N][32];
std::vector<int> e[N];
void dfs(int x, int fa) {
    l[x] = ++ time_stamp;
    dep[x] = dep[fa] + 1, anc[x][0] = fa;
    for (int i = 1; i <= 25; ++i) 
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (int y : e[x]) dfs(y, x);
    r[x] = time_stamp;
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = 25; i >= 0; --i)
        if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (int i = 25; i >= 0; --i)
        if (anc[x][i] != anc[y][i])
            x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}
namespace SegmentTree {
    static const int M = N * 40;
    struct TreeNode {int l, r, sum;} tr[M];
    int rt[M];
    int newnode(int val = 0) {
        ++ id;
        tr[id].l = tr[id].r = -1;
        tr[id].sum = val;
        return id;
    }
    int build(int l, int r) {
        if (l == r) return newnode();
        int mid = (l + r) >> 1;
        int id = newnode();
        tr[id].l = build(l, mid);
        tr[id].r = build(mid + 1, r);
        return id;
    }
    int modify(int x, int l, int r, int p, int v) {
        if (l == r) return newnode(tr[x].sum + v);
        int mid = (l + r) >> 1;
        int id = newnode();
        tr[id] = tr[x];
        if (p <= mid) tr[id].l = modify(tr[x].l, l, mid, p, v);
        else          tr[id].r = modify(tr[x].r, mid + 1, r, p, v);
        tr[id].sum = tr[tr[id].l].sum + tr[tr[id].r].sum;
        return id;
    }
    int update(int p, int v) {
        rt[cnt + 1] = modify(rt[cnt], 1, n, p, v);
        return rt[++ cnt];
    }
    int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[x].sum;
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid && l <= qr) ans += query(tr[x].l, l, mid, ql, qr);
        if (qr >  mid && r >= ql) ans += query(tr[x].r, mid + 1, r, ql, qr);
        return ans;
    }
}
using namespace SegmentTree;
namespace Bfs {
    struct node {
        int dfn, id;
        node(int dfn = 0, int id = 0): dfn(dfn), id(id) {}
        bool operator < (const node &a) const {return dfn < a.dfn;}
    };
    std::set<node> set[N];
    std::queue<int> qu;
    void bfs() {
        qu.emplace(1);
        while (qu.size()) {
            int x = qu.front(); qu.pop();
            auto it = set[col[x]].emplace(l[x], x).first;
            auto pre = std::prev(it); auto nxt = std::next(it);
            update(l[x], 1);
            if (it == set[col[x]].begin()) { 
                if (set[col[x]].size() != 1) update(l[lca(x, nxt -> id)], -1);
            } else {
                if (nxt == set[col[x]].end()) update(l[lca(x, pre -> id)], -1);
                else {
                    int lca1 = lca(pre -> id, nxt -> id);
                    int lca2 = lca(pre -> id, it -> id);
                    int lca3 = lca(nxt -> id, it -> id);
                    if (lca1 == lca2) update(l[lca3], -1);
                    else update(l[lca2], -1);
                } 
            }
            ver[dep[x]] = rt[cnt];
            for (int y : e[x]) qu.emplace(y);
        }
    }
}
using namespace Bfs;
void solve() {
	time_stamp = lastans = maxdep = id = 0;
    scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) e[i].clear();
    for (int i = 1; i <= n; ++i) l[i] = r[i] = 0;
	for (int i = 1; i <= n; ++i) {
        scanf("%d", col + i);
        if (set[col[i]].size()) set[col[i]].clear();
    }
    for (int i = 2; i <= n; ++i) {
        static int fa;
        scanf("%d", &fa);
        e[fa].eb(i);
    }
    dfs(1, 0);
    maxdep = dep[std::max_element(dep + 1, dep + n + 1) - dep];
    rt[cnt = 1] = build(1, n);
	bfs();
    while (q--) {
        static int x, y;
        scanf("%d%d", &x, &y);
        x ^= lastans, y ^= lastans;
        lastans = query(ver[std::min(dep[x] + y, maxdep)], 1, n, l[x], r[x]);
        printf("%d\n", lastans);
    }
}
signed main() {
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}