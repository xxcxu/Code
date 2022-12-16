#include <bits/stdc++.h>
using ll = int64_t;
static constexpr int N = 1e5 + 5;
int n, m, k, a[N], b[N], bel[N], sum[N];
ll ans[N];
class Query {
    public: int l, r, id;
    public: ll ans;
    public: bool operator < (const Query &a) {return bel[l] == bel[a.l] ? r < a.r : l < a.l;}
} q[N];
std::vector<std::tuple<int, int, int>> v[N];
auto main() -> decltype(0) {
    scanf("%d%d%d", &n, &m, &k);

    if (k > 14) {for (int i = 1; i <= m; ++i) puts("0"); return 0;}

    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= m; ++i) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;

    std::vector<int> bucket;
    for (int i = 0; i < (1 << 14); ++i)
        if (__builtin_popcount(i) == k)
            bucket.emplace_back(i);

    int size = std::sqrt(n);
    for (int i = 1; i <= n; ++i) bel[i] = (i - 1) / size + 1;

    std::sort(q + 1, q + m + 1);

    for (int i = 1; i <= n; ++i) {
        for (int x : bucket) ++ b[a[i] ^ x];
        sum[i] = b[a[i + 1]];
    }
    std::memset(b, 0, sizeof b);

    for (int i = 1, l = 1, r = 0; i <= m; ++i) {
        int ql = q[i].l, qr = q[i].r;
        if (l < ql) v[r].emplace_back(l, ql - 1, -i);
        if (l > ql) v[r].emplace_back(ql, l - 1, i);
        while (l < ql) q[i].ans += sum[l - 1], ++ l;
        while (l > ql) q[i].ans -= sum[l - 2], -- l;
        if (r < qr) v[l - 1].emplace_back(r + 1, qr, -i);
        if (r > qr) v[l - 1].emplace_back(qr + 1, r, i);
        while (r < qr) q[i].ans += sum[r], ++ r;
        while (r > qr) q[i].ans -= sum[r - 1], -- r;
    }

    for (int i = 1, l, r, id; i <= n; ++i) {
        for (int j : bucket) ++ b[a[i] ^ j];
        for (auto x : v[i]) {
            std::tie(l, r, id) = x;
            for (int j = l, tmp = 0; j <= r; ++j) {
                tmp = b[a[j]];
                if (j <= i && !k) -- tmp;
                q[std::abs(id)].ans += tmp * (id < 0 ? -1 : 1);
            }
        }
    }

    for (int i = 1; i <= m; ++i) q[i].ans += q[i - 1].ans;
    for (int i = 1; i <= m; ++i) ans[q[i].id] = q[i].ans;
    for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
    return 0;
}