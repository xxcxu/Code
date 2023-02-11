#include <bits/stdc++.h>
static const int N = 100005, inf = N;
int n, m, k;
int a[N], b[N], pre[N], nxt[N];
std::map<int, int> map;
#define ls (x << 1)
#define rs (x << 1 | 1)
int min[N << 2], max[N << 2];
void pushup(int x) {
    min[x] = std::min(min[ls], min[rs]);
    max[x] = std::max(max[ls], max[rs]);
    return void();
}
void build(int x, int l, int r) {
    if (l == r) {
        min[x] = nxt[l];
        max[x] = pre[l];
        return void();
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    return pushup(x);
}
int query_min(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return min[x];
    int mid = (l + r) >> 1, ans = inf;
    if (ql <= mid) ans = std::min(ans, query_min(ls, l, mid, ql, qr));
    if (qr >  mid) ans = std::min(ans, query_min(rs, mid + 1, r, ql, qr));
    return ans;
}
int query_max(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return max[x];
    int mid = (l + r) >> 1, ans = -inf;
    if (ql <= mid) ans = std::max(ans, query_max(ls, l, mid, ql, qr));
    if (qr >  mid) ans = std::max(ans, query_max(rs, mid + 1, r, ql, qr));
    return ans;
}
signed main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) b[i] = k ^ a[i];
    for (int i = 1; i <= n; ++i) {
        pre[i] = map[b[i]] ? map[b[i]] : 0;
        map[a[i]] = i;
    }
    map.clear();
    for (int i = n; i >= 1; --i) {
        nxt[i] = map[b[i]] ? map[b[i]] : n + 1;
        map[a[i]] = i;
    }
    build(1, 1, n);
    while (m--) {
        static int l, r;
        scanf("%d%d", &l, &r);
        int min = query_min(1, 1, n, l, r);
        int max = query_max(1, 1, n, l, r);
        if (min <= r || max >= l) puts("yes");
        else puts("no");
    }
    return 0;
}