#include <bits/stdc++.h>
using ll = long long;
static const int N = 100005, inf = 1e9 + 1;
int n;
int c[N], d[N], min[N];
ll ans;
struct node {int a, b;} a[N];
struct sgt{
    int tr[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void build(int x, int l, int r, int op) {
        if (l == r) {
            tr[x] = op ? a[l].a : a[l].b;
            return void();
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid, op); build(rs, mid + 1, r, op);
        tr[x] = std::max(tr[ls], tr[rs]);
    }
    int query(int x, int l, int r, int ql, int qr) {
        if (qr < ql) return 0;
        if (ql <= l && r <= qr) return tr[x];
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = std::max(ans, query(ls, l, mid, ql, qr));
        if (qr >  mid) ans = std::max(ans, query(rs, mid + 1, r, ql, qr));
        return ans;
    }
} t1, t2;
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].a, &a[i].b);
    for (int i = 1; i <= n; ++i) c[i] = a[i].b;
    for (int i = 1; i <= n; ++i) d[i] = a[i].a;

    std::sort(a + 1, a + n + 1, [](node &a, node &b) {return a.a < b.a;});
    std::sort(d + 1, d + n + 1);
    t1.build(1, 1, n, 0);
    for (int i = 1; i <= n; ++i) {
        int p = std::lower_bound(d + 1, d + n + 1, a[i].a) - d;
        if (p > n) continue;
        if (i == n && p == n) continue;
        if (p == i) ++ p;
        ll res = 0;
        if (p > i) res = std::max(res, 2ll * a[i].a * std::min(a[i].b, t1.query(1, 1, n, p, n)));
        if (p < i) res = std::max(res, 2ll * a[i].a * std::min(a[i].b, std::max(t1.query(1, 1, n, p, i - 1), t1.query(1, 1, n, i + 1, n))));
        ans = std::max(ans, res);
    }

    std::sort(a + 1, a + n + 1, [](node &a, node &b) {return a.b < b.b;});
    std::sort(c + 1, c + n + 1);
    t2.build(1, 1, n, 1);
    for (int i = 1; i <= n; ++i) {
        int p = std::lower_bound(c + 1, c + n + 1, a[i].a) - c;
        if (p > n) continue;
        if (i == n && p == n) continue;
        if (p == i) ++ p;
        ll res = 0;
        if (p > i) res = std::max(res, 2ll * a[i].a * std::min(a[i].b, t2.query(1, 1, n, p, n)));
        if (p < i) res = std::max(res, 2ll * a[i].a * std::min(a[i].b, std::max(t2.query(1, 1, n, p, i - 1), t2.query(1, 1, n, i + 1, n))));
        ans = std::max(ans, res);
    }
    for (int i = 1; i <= n; ++i) ans = std::max(ans, 1ll * a[i].a * a[i].b);
    if (ans % 2 == 1) printf("%lld.5\n", ans / 2);
    else printf("%lld.0\n", ans / 2);
    return 0;
}