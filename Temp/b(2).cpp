#include <bits/stdc++.h>
#define eb emplace_back
signed main() {
    freopen("1.out", "w", stdout);
    std::vector<int> factor;
    for (int n = 1; n <= 1000; ++n) {
        factor.clear();
        for (int i = 1; i * i <= n; ++i) {
            if (n % i) continue;
            factor.eb(i);
            if (i * i != n) factor.eb(n / i);
        }
        using ll = long long;
        ll ans = -1;
        for (auto i : factor)
            for (auto j : factor) {
                int k = n - i - j;
                if (k <= 0) continue;
                if (n % k == 0) ans = std::max(ans, 1ll * i * j * k);
            }
        printf("%lld\n", ans);
    }
    return 0;
}