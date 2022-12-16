#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e5 + 5, inf = 1e18;
int n, m, ans;
int a[N], c[N], h[N], p[N], f[N], g[N];
void cmax(int &x, int y) {x = std::max(x, y);}
class SegmentTree {
    private: int ls(int x) {return x << 1;}
    private: int rs(int x) {return x << 1 | 1;}
    private: int tr[N << 2], tag[N << 2];
    private: void pushup(int x) {tr[x] = std::max(tr[ls(x)], tr[rs(x)]);}
    private: void pushtag(int x, int v) {tr[x] += v; tag[x] += v;}
    private: void pushdown(int x) {if (!tag[x]) return; pushtag(ls(x), tag[x]); pushtag(rs(x), tag[x]); tag[x] = 0;}
    public: void build(int x, int l, int r) {
        tr[x] = -inf, tag[x] = 0;
        if (l == r) return void();
        int mid = (l + r) >> 1;
        build(ls(x), l, mid); build(rs(x), mid + 1, r);
    }
    public: void update(int x, int l, int r, int p, int v) {
        if (l == r) return cmax(tr[x], v);
        pushdown(x);
        int mid = (l + r) >> 1;
        if (p <= mid) update(ls(x), l, mid, p, v);
        else update(rs(x), mid + 1, r, p, v);
        pushup(x);
    }
    public: void modify(int x, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return pushtag(x, v);
        pushdown(x);
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(ls(x), l, mid, ql, qr, v);
        if (qr > mid) modify(rs(x), mid + 1, r, ql, qr, v);
        pushup(x);
    }
    public: int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[x];
        pushdown(x);
        int mid = (l + r) >> 1, ans = -inf;
        if (ql <= mid) cmax(ans, query(ls(x), l, mid, ql, qr));
        if (qr > mid) cmax(ans, query(rs(x), mid + 1, r, ql, qr));
        return ans;
    }
} t1, t2;
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld%lld%lld", h + i, p + i, c + i);
    for (int i = 1; i <= n; ++i) a[i] = h[i];
    std::sort(a + 1, a + n + 1);
    m = std::unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= n; ++i) h[i] = std::lower_bound(a + 1, a + m + 1, h[i]) - a;
    t1.build(1, 0, m + 1); t2.build(1, 0, m + 1);
    t1.update(1, 0, m + 1, 0, 0); t2.update(1, 0, m + 1, 0, 0);
    for (int i = 1; i <= n; ++i) {
        f[i] = t1.query(1, 0, m + 1, 0, h[i]) + p[i];
        t1.modify(1, 0, m + 1, 0, h[i] - 1, -c[i]);
        t1.update(1, 0, m + 1, h[i], f[i]);
    }
    for (int i = n; i >= 1; --i) {
        g[i] = t2.query(1, 0, m + 1, 0, h[i]) + p[i];
        t2.modify(1, 0, m + 1, 0, h[i] - 1, -c[i]);
        t2.update(1, 0, m + 1, h[i], g[i]);
    }
    for (int i = 1; i <= n; ++i) cmax(ans, f[i] + g[i] - p[i]);
    return printf("%lld\n", ans), 0;
}