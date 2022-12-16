#include <bits/stdc++.h>
 static constexpr int N = 1e5 + 5, M = 2e6 + 5, K = 4e7 + 5;
 int n, m, ans, cnt, tot;
 int last[N], root1[N], son1[M][2], root2[M], son2[K][2], tr[K];
struct Node {
    int w, pre, nxt, id;
    friend bool operator < (const Node &a, const Node &b) {return a.pre < b.pre;}
    friend bool operator < (const Node &a, const int &b) {return a.pre < b;}
} a[N];
void Insert2(int &rt, int old, int l, int r, int x, int w) {
    if (!rt) rt = ++ tot;
    tr[rt] = std::max(tr[old], w);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) son2[rt][1] = son2[old][1], Insert2(son2[rt][0], son2[old][0], l, mid, x, w);
    else son2[rt][0] = son2[old][0], Insert2(son2[rt][1], son2[old][1], mid + 1, r, x, w);
}
void Insert1(int &rt, int old, int l, int r, int nxt, int x, int w) {
    if (!rt) rt = ++ cnt;
    Insert2(root2[rt], root2[old], 0, n + 1, x, w);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (nxt <= mid) son1[rt][1] = son1[old][1], Insert1(son1[rt][0], son1[old][0], l, mid, nxt, x, w);
    else son1[rt][0] = son1[old][0], Insert1(son1[rt][1], son1[old][1], mid + 1, r, nxt, x, w);
}
int Query2(int rt, int l, int r, int ql, int qr) {
    if (!rt) return 0;
    if (ql <= l && r <= qr) return tr[rt];
    int mid = (l + r) >> 1, ans = 0;
    if (ql <= mid) ans = std::max(ans, Query2(son2[rt][0], l, mid, ql, qr));
    if (qr > mid) ans = std::max(ans, Query2(son2[rt][1], mid + 1, r, ql, qr));
    return ans;
}
int Query1(int rt, int l, int r, int ql, int qr, int L, int R) {
    if (!rt) return 0;
    if (ql <= l && r <= qr) return Query2(root2[rt], 0, n + 1, L, R);
    int mid = (l + r) >> 1, ans = 0;
    if (ql <= mid) ans = std::max(ans, Query1(son1[rt][0], l, mid, ql, qr, L, R));
    if (qr > mid) ans = std::max(ans, Query1(son1[rt][1], mid + 1, r, ql, qr, L, R));
    return ans;
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i].w);
        a[i].pre = last[a[i].w]; a[i].nxt = n + 1;
        a[a[i].pre].nxt = i; last[a[i].w] = i; a[i].id = i;
    } std::stable_sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i) Insert1(root1[i], root1[i - 1], 0, n + 1, a[i].nxt, a[i].id, a[i].w);
    for (int i = 1, x, y, l, r, p; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        l = std::min((x + ans) % n + 1, (y + ans) % n + 1);
        r = std::max((x + ans) % n + 1, (y + ans) % n + 1);
        p = std::lower_bound(a + 1, a + n + 1, l) - a - 1;
        ans = Query1(root1[p], 0, n + 1, r + 1, n + 1, l, r);
        printf("%d\n", ans);
    } return 0;
}