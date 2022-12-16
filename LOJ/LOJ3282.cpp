#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5, inf = 0x3f3f3f3f;
int n, m, ans = inf, dist;
int dis[N];
class node {public: int t, l, r, c;} a[N];
using pii = std::pair<int, int>;
std::multiset<pii> q;
bool vis[N];
void Push(int x) {q.emplace(dist + a[x].c, x); vis[x] = true;}
void cmin(int &x, int y) {x = std::min(x, y);}
class Segment_Tree {
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    private: int tr[N << 2];
    private: void pushup(int rt) {tr[rt] = std::min(tr[ls], tr[rs]);}
    public: Segment_Tree() {std::memset(tr, 0x3f, (n * 4 + 1) * sizeof(int));}
    public: void update(int rt, int l, int r, int p, int x) {
        if (l == r) return void(cmin(tr[rt], x));
        int mid = (l + r) >> 1;
        if (p <= mid) update(ls, l, mid, p, x);
        else update(rs, mid + 1, r, p, x);
        pushup(rt);
    }
    public: void modify(int rt, int l, int r, int ql, int qr, int x) {
        if (ql > r || qr < l) return void();
        if (l == r) {
            if (!vis[l]) Push(l);
            tr[rt] = inf;
            return void();
        }
        int mid = (l + r) >> 1;
        if (tr[ls] <= x) modify(ls, l, mid, ql, qr, x);
        if (tr[rs] <= x) modify(rs, mid + 1, r, ql, qr, x);
        pushup(rt);
    }
} T1, T2;
int main() {
    scanf("%d%d", &n, &m);
    std::memset(dis, 0x3f, (m + 1) * sizeof(int));
	for (int i = 1; i <= m; ++i)
        scanf("%d%d%d%d", &a[i].t, &a[i].l, &a[i].r, &a[i].c);
    std::sort(a + 1, a + m + 1, [&](node a, node b) {return a.t < b.t;});
	for (int i = 1; i <= m; ++i) {
        if (a[i].l == 1)
            q.emplace(a[i].c, i), vis[i] = true;
        T1.update(1, 1, m, i, a[i].l - a[i].t);
        T2.update(1, 1, m, i, a[i].l + a[i].t);
    }
    while (q.size()) {
        auto [D, id] = *q.begin(); q.erase(q.begin());
        dis[id] = dist = D;
        if (id > 1) T1.modify(1, 1, m, 1, id - 1, a[id].r - a[id].t + 1);
        if (id < m) T2.modify(1, 1, m, id + 1, m, a[id].r + a[id].t + 1);
    }
    for (int i = 1; i <= m; ++i) if (a[i].r == n) ans = std::min(ans, dis[i]);
    printf("%d\n", ans == inf ? -1 : ans);
	return 0;
}