#include <bits/stdc++.h>
static const int N = 200005;
int n, m, q;
int a[N], b[N], d[N], r[N];
std::vector<int> c[N];
struct TreeNode {
    int s, tag;
} tr[N << 2];
#define ls (x << 1)
#define rs (x << 1 | 1)
void pushup(int x) {tr[x].s = std::min(tr[ls].s, tr[rs].s);}
void pushdown(int x) {
    if (tr[x].tag) {
        tr[ls].s += tr[x].tag, tr[rs].s += tr[x].tag;
        tr[ls].tag += tr[x].tag, tr[rs].tag += tr[x].tag;
        tr[x].tag = 0;
    } return void();
}
void build(int x, int l, int r) {
    if (l == r) {
        tr[x].s = d[l];
        tr[x].tag = 0;
        return void();
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    return pushup(x);
}
void update(int x, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        tr[x].s += v;
        tr[x].tag += v;
        return void();
    }
    int mid = (l + r) >> 1;
    pushdown(x);
    if (ql <= mid) update(ls, l, mid, ql, qr, v);
    if (qr >  mid) update(rs, mid + 1, r, ql, qr, v);
    return pushup(x);
}
signed main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) b[0] += a[i] < a[1];
    r[0] = 0;
    for (int i = 1; i <= m; ++i) {
        scanf("%d", r + i);
        c[i].resize(r[i] + 1, 0);
        for (int j = 1; j <= r[i]; ++j) {
            scanf("%d", &c[i][j]);
            b[i] += c[i][j] < a[1];
        }
    }
    for (int i = 1; i <= n; ++i) d[i] = d[i - 1] + b[i - 1] - r[i - 1];
    for (int i = 1; i <= n; ++i) d[i] -= r[i];
    build(1, 0, m);
    while (q--) {
        static int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        if (c[x][y] < a[1] && z > a[1]) {
            -- b[x];
            if (x + 1 <= m) update(1, 0, m, x + 1, m, -1);
        }
        if (c[x][y] > a[1] && z < a[1]) {
            ++ b[x];
            if (x + 1 <= m) update(1, 0, m, x + 1, m, 1);
        }
        puts(tr[1].s < 0 ? "0" : "1");
        c[x][y] = z;
    }
    return 0;
}