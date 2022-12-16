#include <bits/stdc++.h>
using ll = long long;
static constexpr int N = 2e5 + 5, M = 1e5 + 5;
int n, m, a[N], b[N], c[N], d[N];
void add(int x, int v) {for (x += M; x <= n + M; x += x & -x) c[x] += v;}
int ask(int x) {int ans = 0; for (x += M; x; x -= x & -x) ans += c[x]; return ans;}
bool check(int x) {
    ll ans = 0;
    for (int i = 1; i <= n; ++i) b[i] = (a[i] < x ? -1 : 1);
    for (int i = 1; i <= n; ++i) d[i] = d[i - 1] + b[i];
    add(0, 1);
    for (int i = 1; i <= n; ++i) ans += ask(d[i]), add(d[i], 1);
    for (int i = 1; i <= n; ++i) add(d[i], -1);
    add(0, -1);
    return 2ll * ans >= 1ll * n * (n + 1) / 2;
}
signed main() {
    freopen("median.in", "r", stdin);
    freopen("median.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) m = std::max(m, a[i]);
    int l = 0, r = m;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    printf("%d\n", l);
    return 0;
}