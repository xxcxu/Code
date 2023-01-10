#include <bits/stdc++.h>
template<typename DataType>
DataType read() {
	DataType t = 0, f = 0;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
	for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
	return f ? ~t + 1 : t;
}
#define int long long
#define eb emplace_back
static const int N = 50005, inf = 5e13 + 5;
int n, m, q, id;
int max[N << 2], hmax[N << 2];
int tag[N << 2], htag[N << 2];
int ans[N * 10];
struct node {
    int l1, r1, l2, r2, v;
    node(int l1 = 0, int r1 = 0, int l2 = 0, int r2 = 0, int v = 0):
        l1(l1), r1(r1), l2(l2), r2(r2), v(v) {}
};
std::vector<node> que[N], ins[N], ers[N];
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
void pushtag(int x, int v, int hv) {
    htag[x] = std::max(htag[x], tag[x] + hv);
    hmax[x] = std::max(hmax[x], max[x] + hv);
    tag[x] += v, max[x] += v;
    return void();
}
void pushdown(int x) {
    if (htag[x] || tag[x]) {
        pushtag(ls(x), tag[x], htag[x]);
        pushtag(rs(x), tag[x], htag[x]);
        tag[x] = htag[x] = 0;
    }
    return void();
}
void pushup(int x) {
    max[x] = std::max(max[ls(x)], max[rs(x)]);
    hmax[x] = std::max(hmax[ls(x)], hmax[rs(x)]);
    return void();
}
void modify(int x, int l, int r, int ql, int qr, int v) {
    if (ql == l && r == qr) return pushtag(x, v, std::max(v, 0ll));
    int mid = (l + r) >> 1;
    pushdown(x);
    if (qr <= mid)     modify(ls(x), l, mid, ql, qr, v);
    else if (ql > mid) modify(rs(x), mid + 1, r, ql, qr, v);
    else modify(ls(x), l, mid, ql, mid, v), modify(rs(x), mid + 1, r, mid + 1, qr, v);
    return pushup(x);
}
int query(int x, int l, int r, int ql, int qr) {
    if (ql == l && r == qr) return hmax[x];
    int mid = (l + r) >> 1;
    pushdown(x);
    if (qr <= mid)     return query(ls(x), l, mid, ql, qr);
    else if (ql > mid) return query(rs(x), mid + 1, r, ql, qr);
    else return std::max(query(ls(x), l, mid, ql, mid), query(rs(x), mid + 1, r, mid + 1, qr));
}
void clear() {modify(1, 1, n, 1, n, inf); ++ id;}
void work(const std::vector<node> &upd, int sign) {for (const auto &v : upd) modify(1, 1, n, v.r1, v.r2, v.v * sign);}
void answer(const std::vector<node> &qry) {for (const auto &v : qry) ans[v.v] = std::max(ans[v.v], query(1, 1, n, v.r1, v.r2) - id * inf);}
void solve(const std::vector<node> &upd, const std::vector<node> &qry, int l, int r) {
    if (!qry.size()) return;
    if (l == r) {
        work(upd, 1), answer(qry), work(upd, -1);
        return clear();
    }
    int mid = (l + r) >> 1;
    for (int i = l - 1; i <= r + 1; ++i) que[i].clear(), ins[i].clear(), ers[i].clear();
    std::vector<node> ql, qr, tl, tr, ul, ur;
    for (const auto &v : qry) {
        if (v.l2 <= mid) ql.eb(v);
        else if (v.l1 > mid) qr.eb(v);
        else que[v.l1].eb(v), que[v.l2].eb(v);
    }
    for (const auto &v : upd) {
        if (v.l2 <= mid) ins[v.l2].eb(v), ers[v.l1 - 1].eb(v);
        else if (v.l1 > mid) ins[v.l1].eb(v), ers[v.l2 + 1].eb(v);
        else ins[mid].eb(v), ins[mid + 1].eb(v), ers[v.l1 - 1].eb(v), ers[v.l2 + 1].eb(v);
    }
    for (int i = mid    ; i >= l - 1; --i) work(ers[i], -1), work(ins[i], 1), answer(que[i]); clear();
    for (int i = mid + 1; i <= r + 1; ++i) work(ers[i], -1), work(ins[i], 1), answer(que[i]); clear();
    for (const auto &v : upd) {
        if (v.l2 <= mid) (v.l1 == l && v.l2 == mid ? tl : ul).eb(v);
        else if (v.l1 > mid) (v.l1 == mid + 1 && v.l2 == r ? tr : ur).eb(v);
        else {
            (v.l1 == l ? tl : ul).eb(v.l1,    v.r1, mid,  v.r2, v.v);
            (v.l2 == r ? tr : ur).eb(mid + 1, v.r1, v.l2, v.r2, v.v);
        }
    }
    work(tl, 1); solve(ul, ql, l, mid);     work(tl, -1); clear();
    work(tr, 1); solve(ur, qr, mid + 1, r); work(tr, -1); clear(); 
}
signed main() {
    std::vector<node> upd, qry;
	n = read<int>(), m = read<int>(), q = read<int>();
    for (int i = 1; i <= m; ++i) {
        static int l1, r1, l2, r2, x;
		l1 = read<int>(), r1 = read<int>(), l2 = read<int>(), r2 = read<int>(), x = read<int>();
        upd.eb(l1, r1, l2, r2, x);
    }
    for (int i = 1; i <= q; ++i) {
        static int l1, r1, l2, r2, x;
		l1 = read<int>(), r1 = read<int>(), l2 = read<int>(), r2 = read<int>(); x = i;
        qry.eb(l1, r1, l2, r2, x);
    }
    solve(upd, qry, 1, n);
    for (int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);
    return 0;
}