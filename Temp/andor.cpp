#include <bits/stdc++.h>
#define count1 __builtin_popcount
static constexpr int N = 1e5 + 5;
int n, q, max, a[N];
class SegmentTree {
    #define ls(x) (x << 1)
    #define rs(x) (x << 1 | 1)
    public: class TreeNode {
        public: int _and, _or, _val;
        public: TreeNode(int _and = -1, int _or = 0, int _val = 0):
            _and(_and), _or(_or), _val(_val) {}
        public: TreeNode operator + (const TreeNode &a) {
            return TreeNode(_and & a._and, _or | a._or, _val + a._val);
        }
    } tr[N << 2];
    private: void pushup(int x) {tr[x] = tr[ls(x)] + tr[rs(x)];}
    public: void build(int x, int l, int r) {
        int mid = (l + r) >> 1;
        if (l == r) return void();
        build(ls(x), l, mid); build(rs(x), mid + 1, r);
        pushup(x);
    }
    public: void update(int x, int l, int r, int p, int v) {
        if (l == r) return void(tr[x] = TreeNode(v, v, 1));
        int mid = (l + r) >> 1;
        if (p <= mid) update(ls(x), l, mid, p, v);
        else update(rs(x), mid + 1, r, p, v);
        pushup(x);
    }
    public: TreeNode ask(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[x];
        int mid = (l + r) >> 1; TreeNode ans;
        if (ql <= mid) ans = ans + ask(ls(x), l, mid, ql, qr);
        if (qr > mid) ans = ans + ask(rs(x), mid + 1, r, ql, qr);
        return ans;
    }
    #undef ls(x)
    #undef rs(x)
} Tree[32];
SegmentTree::TreeNode tmp[32];
bool check() {
    static int l, r;
    scanf("%d%d", &l, &r);
    for (int i = 0; i <= max; ++i) tmp[i] = Tree[i].ask(1, 1, n, l, r);
    for (int k = 0; k <= max; ++k) {
        int A = 0, B = -1, C = 0, Acnt = 0, Bcnt = 0, Ccnt = 0;
        for (int i = 0; i < k; ++i) A |= tmp[i]._or, Acnt += tmp[i]._val;
        for (int i = k + 1; i <= max; ++i) B &= tmp[i]._and, Bcnt += tmp[i]._val;
        C = tmp[k]._and, Ccnt = tmp[k]._val;
        if (A == (B & C) && Acnt > 0 && Bcnt + Ccnt > 0) return true;
        if (C == -1 || count1(C) != k) continue;
        if (Ccnt > 1) if ((A | C) == (B & C)) return true;
    } return false;
}
signed main() {
    freopen("andor.in", "r", stdin);
    freopen("andor.out", "w", stdout);
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) {
        int len = count1(a[i]);
        Tree[len].update(1, 1, n, i, a[i]);
        max = std::max(max, len);
    } 
    for (int i = 0; i <= max; ++i) Tree[i].build(1, 1, n);
    while (q--) puts(check() ? "YES" : "NO");
    return 0;
}