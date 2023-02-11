#include <bits/stdc++.h>
#define eb emplace_back
#define ls son[x][0]
#define rs son[x][1]
using pii = std::pair<int, int>;
static const int N = 200005, M = N << 5, inf = 0x3fffffff;
int n, m, K, q, tot, sign;
int tr[M], num[M], son[M][2];
int c[N], fa[N], rt[N], len[N], last[N];
struct Edge {int x, y, z; Edge(int x = 0, int y = 0, int z = 0): x(x), y(y), z(z) {}} edge[N];
std::multiset<int> ans, s[N << 2];
std::vector<pii> e[N];
int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
void pushup(int x) {tr[x] = std::min(tr[ls], tr[rs]);}
void ins(int &x, int l, int r, int p, int v) {
    if (!x) x = ++ tot;
    if (l == r) {
        if (!num[x]) num[x] = ++ sign;
        s[num[x]].insert(v);
        tr[x] = *s[num[x]].begin();
        return void();
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ins(ls, l, mid, p, v);
    else ins(rs, mid + 1, r, p, v);
    return pushup(x);
}
void del(int &x, int l, int r, int p, int v) {
    if (l == r) {
        s[num[x]].erase(s[num[x]].find(v));
        tr[x] = s[num[x]].size() ? *s[num[x]].begin() : inf;
        return void();
    }
    int mid = (l + r) >> 1;
    if (p <= mid) del(ls, l, mid, p, v);
    else del(rs, mid + 1, r, p, v);
    return pushup(x);
}
int query(int x, int l, int r, int ql, int qr) {
    if (!x || ql > qr) return inf;
    if (ql <= l && r <= qr) return tr[x];
    int mid = (l + r) >> 1, ans = inf;
    if (ql <= mid) ans = std::min(ans, query(ls, l, mid, ql, qr));
    if (qr >  mid) ans = std::min(ans, query(rs, mid + 1, r, ql, qr));
    return ans;
}
int query(int x) {
    int lx = query(rt[x], 1, K, 1, c[x] - 1);
    int rx = query(rt[x], 1, K, c[x] + 1, K);
    return std::min(lx, rx);
}
void dfs(int x, int pre) {
    fa[x] = pre;
    for (auto [y, z] : e[x]) if (y != pre) {
        len[y] = z;
        dfs(y, x);
        ins(rt[x], 1, K, c[y], len[y]);
    }
    ans.insert(last[x] = query(x));
    return void();
}
void kruskal() {
    std::sort(edge + 1, edge + m + 1, [&](Edge a, Edge b) {return a.z < b.z;});
    for (int i = 1; i <= m; ++i) {
        int x = edge[i].x, y = edge[i].y, z = edge[i].z;
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            fa[fx] = fy;
            e[x].eb(y, z), e[y].eb(x, z);
        }
    } return void();
}
signed main() {
    std::memset(tr, 0x3f, sizeof tr);
    scanf("%d%d%d%d", &n, &m, &K, &q);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) {
        static int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edge[i] = Edge(u, v, w);
    }
    for (int i = 1; i <= n; ++i) scanf("%d", c + i);
    kruskal();
    dfs(1, 0);
    while (q--) {
        static int x, C;
        scanf("%d%d", &x, &C);
        int fx = fa[x];
        ans.erase(ans.find(last[x]));
        if (fx) ans.erase(ans.find(last[fx]));
        if (fx) del(rt[fx], 1, K, c[x], len[x]);
        c[x] = C;
        ans.insert(last[x] = query(x));
        if (fx) ins(rt[fx], 1, K, c[x], len[x]);
        if (fx) ans.insert(last[fx] = query(fx));
        printf("%d\n", *ans.begin());
    }
    return 0;
}