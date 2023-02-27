#include <bits/stdc++.h>
static const int N = 2000005, inf = 1e9;
int n, m, q, K;
class Matrix {
    public: int a[5][5];
    public: friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix ans;
        for (int i = 0; i < K; ++i)
            for (int j = 0; j < K; ++j) {
                ans.a[i][j] = inf;
                for (int k = 0; k < K; ++k)
                    ans.a[i][j] = std::min(ans.a[i][j], a.a[i][k] + b.a[k][j]);
            }
        return ans;
    }
    public: void Unit() {
        for (int i = 0; i < K; ++i) 
            for (int j = 0; j < K; ++j)
                if (i == j) a[i][j] = 0;
                else a[i][j] = inf;
        return void();
    }
    public: void Unit2() {
        for (int i = 0; i < K; ++i) 
            for (int j = 0; j < K; ++j)
                a[i][j] = inf;
        return void();
    }
};
class SegmentTree {
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    public: class TreeNode {public: Matrix mat;} tr[N];
    public: void update(int x, int l, int r, int p, int a, int b, int v) {
        if (l == r) {
            tr[x].mat.a[a][b] = v;
            return void();
        }
        int mid = (l + r) >> 1;
        if (p <= mid) update(ls, l, mid, p, a, b, v);
        else update(rs, mid + 1, r, p, a, b, v);
        tr[x].mat = tr[ls].mat * tr[rs].mat;
    }
    public: Matrix query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[x].mat;
        int mid = (l + r) >> 1;
        if (ql > mid) return query(rs, mid + 1, r, ql, qr);
        else if (qr <= mid) return query(ls, l, mid, ql, qr);
        else return query(ls, l, mid, ql, qr) * query(rs, mid + 1, r, ql, qr);
    }
} Seg;
signed main() {
    scanf("%d%d%d%d", &K, &n, &m, &q);
    int t = (n - 1) / K;
    for (int i = 1; i <= t * 4; ++i) Seg.tr[i].mat.Unit2();
    for (int i = 0; i < m; ++i) {
        static int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        Seg.update(1, 0, t, u / K, u % K, v % K, w);
    }
    while (q--) {
        static int S, T;
        scanf("%d%d", &S, &T);
        if (S / K >= T / K) {puts("-1"); continue;}
        Matrix ans = Seg.query(1, 0, t, S / K, T / K - 1);
        if (ans.a[S % K][T % K] == inf) puts("-1");
        else printf("%d\n", ans.a[S % K][T % K]);
    } return 0;
}