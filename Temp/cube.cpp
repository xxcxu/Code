#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5, P = 95542721;
int n, q, lable, a[N]; 
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
class SegmentTree2 {
    #define ls(x) (x << 1)
    #define rs(x) (x << 1 | 1)
    private: class TreeNode {
        public: int s1, s2, lazy;
    } tr[N << 2];
    private: void pushup(int x) {
        tr[x].s1 = inc(tr[ls(x)].s1, tr[rs(x)].s1);
        tr[x].s2 = inc(tr[ls(x)].s2, tr[rs(x)].s2);
    }
    private: void pushdown(int x) {
        tr[ls(x)].lazy ^= tr[x].lazy;
        tr[rs(x)].lazy ^= tr[x].lazy;
        if (tr[ls(x)].lazy) std::swap(tr[ls(x)].s1, tr[ls(x)].s2);
        if (tr[rs(x)].lazy) std::swap(tr[rs(x)].s1, tr[rs(x)].s2);
        tr[x].lazy = 0;
    }
    public: void build(int x, int l, int r) {
        tr[x].lazy = 0;
        if (l == r) {
            tr[x].s1 = a[l];
            tr[x].s2 = mul(a[l], mul(a[l], a[l]));
            return void();
        }
        int mid = (l + r) >> 1;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        pushup(x);
    }
    public: void modify(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            std::swap(tr[x].s1, tr[x].s2);
            tr[x].lazy ^= 1;
            return void();
        }
        pushdown(x);
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(ls(x), l, mid, ql, qr);
        if (qr > mid) modify(rs(x), mid + 1, r, ql, qr);
        pushup(x);
    }
    public: int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[x].s1;
        pushdown(x);
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = inc(ans, query(ls(x), l, mid, ql, qr));
        if (qr > mid) ans = inc(ans, query(rs(x), mid + 1, r, ql, qr));
        return ans;
    }
} tr;
signed main() {
    freopen("cube.in", "r", stdin);
    freopen("cube.out", "w", stdout);
    scanf("%d%d", &n, &lable);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    scanf("%d", &q);
    tr.build(1, 1, n);
    while (q--) {
        static int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) printf("%d\n", tr.query(1, 1, n, l, r));
        if (op == 2) tr.modify(1, 1, n, l, r);
    }
}