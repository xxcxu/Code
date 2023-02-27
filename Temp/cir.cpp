# include <bits/stdc++.h>

using LL = long long;

static const int N = 1000005;
int t;
int mu[N], vis[N], prime[N];
LL n, r, R, ans;

void init(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++ t] = i, mu[i] = -1;
        for (int j = 1; prime[j] * i <= n; ++j) {
            mu[i * prime[j]] = i % prime[j] ? -mu[i] : 0;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }   
}
signed main() {
    freopen("cir.in", "r", stdin);
    freopen("cir.out", "w", stdout);
    init(N - 1);
    scanf("%lld%lld", &n, &r); -- n;    
    if (!n) return puts("0"), 0;
    R = 1e12 / r / r;
    if (R * r * r == 1e12) -- R;
    for (LL d = 1; d * d <= R; ++d) {
        LL k = R / (d * d);
        for (LL i = 1; i <= n / d && i * i <= k; ++i) {
            LL p = k - 1LL * i * i;
            ans += mu[d] * std::min(LL(std::sqrt(p)), n / d);
        }
    }
    return printf("%lld\n", ans + 2), 0;
}