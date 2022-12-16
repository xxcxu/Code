#include <bits/stdc++.h>
#define int long long
static constexpr int N = 1e6 + 5;
int n, cnt, prime[N], vis[N];
void init(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++ cnt] = i;
        for (int j = 1; i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = true;
            if (!(i % prime[j])) break;
        }
    }
}
void solve() {
    scanf("%lld", &n);
    if (n % 2 == 1)
        for (int i = 2; i <= cnt; ++i) {
            int p = prime[i];
            if (n % p) return printf("%lld %lld\n", p * n, (p - 1) * n), void();
        }
    else printf("%lld %lld\n", 2 * n, n);
}
signed main() {
    freopen("Z.in", "r", stdin);
    freopen("Z.out", "w", stdout);
    init(N - 1);
    int t; scanf("%lld", &t);
    while (t--) solve();
}