#include <bits/stdc++.h>
static const int N = 100005, inf = 0x7fffffff;
int n, m, a[N];
int max[N << 2], maxh[N << 2];
int tagc[N << 2], htagc[N << 2];
int tagp[N << 2], htagp[N << 2];
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
void pushup(int x) {
    max[x] = std::max(max[ls(x)], max[rs(x)]);
    maxh[x] = std::max(maxh[ls(x)], maxh[rs(x)]);
    return void();
}
void cov(int x, int v, int hv) {
    max[x] = tagc[x] = v;
    maxh[x] = std::max(maxh[x], hv);
    htagc[x] = std::max(htagc[x], hv);
}
void add(int x, int v, int hv) {
    if (tagc[x] != inf) return cov(x, tagc[x] + v, tagc[x] + hv);
    htagp[x] = std::max(htagp[x], tagp[x] + hv);
    tagp[x] += v, max[x] += v;
    maxh[x] = std::max(maxh[x], max[x] - tagp[x] + htagp[x]);
}
void pushdown(int x) {
    add(ls(x), tagp[x], htagp[x]);
    add(rs(x), tagp[x], htagp[x]);
    tagp[x] = htagp[x] = 0;
    if (tagc[x] != inf) {
        cov(ls(x), tagc[x], htagc[x]);
        cov(rs(x), tagc[x], htagc[x]);
        tagc[x] = inf;
    }
}
void build(int x, int l, int r) {
    tagc[x] = inf, htagc[x] = -inf;
    if (l == r) {
        max[x] = maxh[x] = a[l];
        return void();
    }
    int mid = (l + r) >> 1;
    build(ls(x), l, mid); build(rs(x), mid + 1, r);
    return pushup(x);
}
int query_max(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return max[x];
    int mid = (l + r) >> 1, ans = -inf;
    pushdown(x);
    if (ql <= mid) ans = std::max(query_max(ls(x), l, mid, ql, qr), ans);
    if (qr >  mid) ans = std::max(query_max(rs(x), mid + 1, r, ql, qr), ans);
    return ans;
}
int query_maxh(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return maxh[x];
    int mid = (l + r) >> 1, ans = -inf;
    pushdown(x);
    if (ql <= mid) ans = std::max(query_maxh(ls(x), l, mid, ql, qr), ans);
    if (qr >  mid) ans = std::max(query_maxh(rs(x), mid + 1, r, ql, qr), ans);
    return ans;
}
void modify_add(int x, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) return add(x, v, std::max(v, 0));
    int mid = (l + r) >> 1;
    pushdown(x);
    if (ql <= mid) modify_add(ls(x), l, mid, ql, qr, v);
    if (qr >  mid) modify_add(rs(x), mid + 1, r, ql, qr, v);
    return pushup(x);
}
void modify_cov(int x, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) return cov(x, v, v);
    int mid = (l + r) >> 1;
    pushdown(x);
    if (ql <= mid) modify_cov(ls(x), l, mid, ql, qr, v);
    if (qr >  mid) modify_cov(rs(x), mid + 1, r, ql, qr, v);
    return pushup(x);
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    build(1, 1, n);
    scanf("%d", &m);
    while (m--) {
        static char op[2];
        static int l, r, x;
        scanf("%s%d%d", op, &l, &r);
        if (op[0] == 'Q') {printf("%d\n", query_max(1, 1, n, l, r));}
        if (op[0] == 'A') {printf("%d\n", query_maxh(1, 1, n, l, r));}
        if (op[0] == 'P') {scanf("%d", &x); modify_add(1, 1, n, l, r, x);}
        if (op[0] == 'C') {scanf("%d", &x); modify_cov(1, 1, n, l, r, x);}
    }
    return 0;
}