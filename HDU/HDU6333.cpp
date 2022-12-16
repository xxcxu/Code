#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5, P = 1e9 + 7, inv2 = P / 2 + 1;
int n, m, now = 1, bel[N], ans[N], fac[N], inv[N];
struct node {
    int l, r, id;
    node(int l = 0, int r = 0, int id = 0):
        l(l), r(r), id(id) {}
};
bool cmp1(const node &a, const node &b) {
    if (bel[a.l] == bel[b.l]) return a.r < b.r;
    return a.l < b.l;
}
node q[N];
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
int C(int n, int m) {return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;}
void AddL(int n, int m) {now = (now + C(n, m)) % P; now = 1ll * now * inv2 % P;};
void DelL(int n, int m) {now = now * 2ll % P; now = (now + P - C(n - 1, m)) % P;};
void AddR(int n, int m) {now = (now + C(n, m)) % P;};
void DelR(int n, int m) {now = (now + P - C(n, m + 1)) % P;};
void init() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
    inv[N - 1] = qpow(fac[N - 1], P - 2, P);
    for (int i = N - 2; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % P;
}
signed main() {
    int t; scanf("%d", &t); init();
    for (int i = 1; i <= t; ++i) scanf("%d%d", &n, &m), q[i] = node(n, m, i);
    int size = (int)std::sqrt(t);
    for (int i = 1; i <= t; ++i) bel[i] = i / size + 1;
    std::sort(q + 1, q + t + 1, cmp1);
    int L = 1, R = 0;
    for (int i = 1; i <= t; ++i) {
        while (L < q[i].l) DelL(++ L, R);
        while (R > q[i].r) DelR(L, -- R);
        while (L > q[i].l) AddL(-- L, R);
        while (R < q[i].r) AddR(L, ++ R);
        ans[q[i].id] = now;
    }
    for (int i = 1; i <= t; ++i) printf("%d\n", ans[i]);
	return 0;
}