#include <bits/stdc++.h>
using ll = long long;
static constexpr int N = 5e5 + 5;
int n, q, a[N], b[N];
ll sum[N];
template<int N, int size>
class St_Table {
    private: int f[N][size], g[N][size];
    public: void Init(int n, int *a) {
        for (int i = 1; i <= n; ++i) f[i][0] = a[i], g[i][0] = i;
        for (int j = 1; j <= size; ++j)
            for (int i = 1; i <= n - (1ll << j) + 1; ++i) {
                if (f[i][j - 1] > f[i + (1 << (j - 1))][j - 1])
                    g[i][j] = g[i + (1 << (j - 1))][j - 1],
                    f[i][j] = f[i + (1 << (j - 1))][j - 1];
                else
                    g[i][j] = g[i][j - 1], f[i][j] = f[i][j - 1];
            }
        return void();
    }
    public: int Query(int l, int r) {
        int k = std::log2(r - l + 1);
        return f[l][k] > f[r - (1 << k) + 1][k] ? g[r - (1 << k) + 1][k] : g[l][k];
    }
};
St_Table<N, 25> rmq;
ll calc(int l, int r) {
    int p = rmq.Query(l, r);
    ll pre = sum[p - 1] - sum[l - 1];
    ll suf = sum[r - 1] - sum[p - 1];
    return 1ll * a[p] * (sum[r - 1] - sum[l - 1] + std::min(pre, suf));
}
signed main() {
    freopen("pmyl.in", "r", stdin);
    freopen("pmyl.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i < n; ++i) scanf("%d", b + i);
    rmq.Init(n, a);
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + b[i];
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        static int l, r;
        scanf("%d%d", &l, &r);
        ll ans = 0;
        for (int j = l; j <= r; ++j)
            for (int k = j; k <= r; ++k)
                ans = std::max(ans, calc(j, k));
        printf("%lld\n", ans);
    }
    return 0;
}