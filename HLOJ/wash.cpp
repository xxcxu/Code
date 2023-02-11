#include <bits/stdc++.h>
using ll = long long;
static const int N = 10000005;
int n, m, k, t[N];
ll res, ans[N];
signed main() {
    freopen("wash.in", "r", stdin);
    freopen("wash.out", "w", stdout);
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", t + i);
    for (int i = 1; i <= n; ++i) {
        ll res = 1ll * (n - i + 1) * k;
        res = std::min(res, 1ll * m);
        ans[res] = std::max(ans[res], t[i] + res);
    }
    for (int i = m; i >= 1; --i) ans[i] = std::max(ans[i + 1] - 1, ans[i]);
    for (int i = 1; i <= m; ++i) ans[i] = std::max(ans[i], ans[i - 1]);
    for (int i = 1; i <= m; ++i) res ^= (1ll * ans[i] * i);
    printf("%lld\n", res); 
    return 0;
}