#include <bits/stdc++.h>
#define int long long
using ll = long long;
using pii = std::pair<int, int>;
static constexpr int N = 1e6 + 5, M = 1e6 + 1;
int n, m, v[N], lm[N], rm[N];
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
int lv[N << 2], sl[N << 2];
int gcd(int x, int y) {return !y ? x : gcd(y, x % y);}
void approx(int &x, int &y) {
    int g = gcd(x, y);
    x /= g; y /= g;
}
void pushup(int x) {
    lv[x] = lv[ls(x)] + lv[rs(x)];
    sl[x] = sl[ls(x)] + sl[rs(x)];
}
void update(int x, int l, int r, int p, int L) {
    if (l == r) {
        lv[x] += L * p;
        sl[x] += L;
        return void();
    }
    int mid = (l + r) >> 1;
    if (p <= mid) update(ls(x), l, mid, p, L);
    else update(rs(x), mid + 1, r, p, L);
    pushup(x);
}
pii query(int x, int l, int r, int SLV, int SL) {
    if (l == r) return pii(0, 1);
    int mid = (l + r) >> 1;
    int p = SLV + lv[rs(x)];
    int q = SL + sl[rs(x)] + rm[0];
    if (q == 0) q = 1;
    if (mid <= p / q) {
        pii ans = query(rs(x), mid + 1, r, SLV, SL);
        if (ans.first == 0) return pii(p, q);
        return ans;
    }
    else return query(ls(x), l, mid, SLV + lv[rs(x)], SL + sl[rs(x)]);
}
void change(int x, int a, int b, int c) {
    if (x == 0) {
        rm[x] = c;
        goto pofix;
    }
    update(1, 0, M, v[x], -lm[x]);
    v[x] = a; lm[x] = b; rm[x] = c;
    update(1, 0, M, v[x], lm[x]);
    pofix:
    auto [p, q] = query(1, 0, M, 0, 0);
    approx(p, q);
    printf("%lld/%lld\n", p, q);
}
signed main() {
    freopen("ds.in", "r", stdin);
    freopen("ds.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", v + i);
    for (int i = 0; i <= n; ++i) scanf("%lld", lm + i);
    for (int i = 0; i <= n; ++i) scanf("%lld", rm + i);
    for (int i = 1; i <= n; ++i) update(1, 0, M, v[i], lm[i]);
    auto [p, q] = query(1, 0, M, 0, 0);
    approx(p, q);
    printf("%lld/%lld\n", p, q);
    for (int i = 1; i <= m; ++i) {
        static int t, x, y, z;
        scanf("%lld%lld%lld%lld", &t, &x, &y, &z);
        change(t, x, y, z);
    }
    return 0;
}