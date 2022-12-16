#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5, inf = 1e9 + 7, P = 1e9 + 7;
class Matrix {
    private: int n, m;
    public: int a[2][2];
    public: Matrix(int n = 0, int m = 0, int p = 0): n(n), m(m) {
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) a[i][j] = 0;
        if (p) for (int i = 0; i < n; ++i) a[i][i] = 1;
    }
    public: int* operator [] (int x) & {return a[x];}
    public: const int* operator[](int x) const& {return a[x];}
    public: friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix ans = Matrix(a.n, b.m);
        for (int i = 0; i < a.n; ++i)
            for (int j = 0; j < b.m; ++j)
                for (int k = 0; k < a.m; ++k)
                    ans[i][j] = (ans[i][j] + 1ll * a[i][k] * b[k][j] % P) % P;
        return ans;
    }
    public: friend Matrix operator + (const Matrix &a, const Matrix &b) {
        Matrix ans = Matrix(a.n, a.m, 0);
        assert(a.n == b.n); assert(a.m == b.m);
        for (int i = 0; i < a.n; ++i)
            for (int j = 0; j < a.m; ++j)
                ans[i][j] = (a[i][j] + b[i][j]) % P;
        return ans;
    }
    public: auto Unit() -> void {
        assert(n == m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) 
                a[i][j] = (i == j);
        return void();
    }
    public: auto pd() -> int {
        if (a[0][0] ^ 1) return 0;
        if (a[0][1] ^ 0) return 0;
        if (a[1][0] ^ 0) return 0;
        if (a[1][1] ^ 1) return 0;
        return 1;
    }
    public: friend Matrix operator ^ (Matrix a, int k) {
        Matrix ans = Matrix(a.n, a.m, 1);
        for (; k; k >>= 1, a = a * a)
            if (k & 1) ans = ans * a;
        return ans;
    }
};
int n, m, a[N];
Matrix ans, base;
class SegmentTree {
    public: class TreeNode {public: Matrix v, tag;} tr[N << 2];
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    public: auto Pushup(int rt) -> void {tr[rt].v = tr[ls].v + tr[rs].v;}
    public: auto Pushdown(int rt) -> void {
        if (tr[rt].tag.pd()) return void();
        tr[ls].tag = tr[ls].tag * tr[rt].tag;
        tr[rs].tag = tr[rs].tag * tr[rt].tag;
        tr[ls].v = tr[ls].v * tr[rt].tag;
        tr[rs].v = tr[rs].v * tr[rt].tag;
        tr[rt].tag.Unit();
    }
    public: auto Build(int rt, int l, int r) -> void {
        tr[rt].v =  tr[rt].tag = Matrix(2, 2);
        tr[rt].tag.Unit();
        if (l == r) {
            if (a[l] == 1) tr[rt].v[0][0] = 1;
            else if (a[l] == 2) tr[rt].v[0][0] = tr[rt].v[0][1] = 1;
            else tr[rt].v = ans * (base ^ (a[l] - 2));
            return void();
        } int mid = (l + r) >> 1;
        Build(ls, l, mid); Build(rs, mid + 1, r);
        Pushup(rt);
    }
    public: auto Update(int rt, int l, int r, int ql, int qr, Matrix v) -> void {
        if (ql <= l && r <= qr) {
            tr[rt].v = tr[rt].v * v;
            tr[rt].tag = tr[rt].tag * v;
            return void();
        } Pushdown(rt);
        int mid = (l + r) >> 1;
        if (ql <= mid) Update(ls, l, mid, ql, qr, v);
        if (qr > mid) Update(rs, mid + 1, r, ql, qr, v);
        Pushup(rt);
    }
    public: auto Query(int rt, int l, int r, int ql, int qr) -> int {
        if (ql <= l && r <= qr) return tr[rt].v[0][0];
        Pushdown(rt);
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = (ans + Query(ls, l, mid, ql, qr)) % P;
        if (qr > mid) ans = (ans + Query(rs, mid + 1, r, ql, qr)) % P;
        return ans;
    }
} Tree;
signed main() {
    base = Matrix(2, 2), ans = Matrix(2, 2);
    base[0][0] = base[0][1] = base[1][0] = 1;
    ans[0][0] = ans[0][1] = 1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    Tree.Build(1, 1, n);
    for (int i = 1, opt, l, r, k; i <= m; ++i) {
        scanf("%d%d%d", &opt, &l, &r);
        if (opt & 1) scanf("%d", &k), Tree.Update(1, 1, n, l, r, base ^ k);
        else printf("%d\n", Tree.Query(1, 1, n, l, r));
    } return 0;
}