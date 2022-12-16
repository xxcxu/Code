#include <bits/stdc++.h>
#define int long long
using ll = long long;
static constexpr int N = 1e2 + 5, M = 5e2 + 5;
int T, Case, m, p[N], tot[M];
ll ans, sum, n[N];
bool flag;
std::map<ll, ll> map;
auto GetPrimeFactor(ll x) -> void {
    map.clear();
    for (int i = 2; 1ll * i * i <= x; ++i) {
        if (i > 500) {flag = false; break;}
        while (!(x % i)) ++ map[i], x /= i;
    }
    if (x > 500) flag = false;
    else if (x > 1) map[x] = 1ll;
}
auto Solve(int test_case = 0) -> void {
    scanf("%lld", &m); ans = sum = 0;
    std::memset(tot, 0, sizeof tot);
    for (int i = 1; i <= m; ++i) scanf("%lld%lld", p + i, n + i), tot[p[i]] = n[i];
    for (int i = 1; i <= m; ++i) sum += 1ll * p[i] * n[i];
    for (int i = 0; i <= std::min(sum, 30000ll); ++i) {
        flag = true; ll s2 = 0;
        GetPrimeFactor(sum - i);
        for (auto it : map)
            if (it.second > tot[it.first]) {flag = false; break;}
            else s2 += 1ll * it.first * it.second;
        if (s2 == i && flag) ans = std::max(ans, sum - i);
    }
    printf("Case #%lld: ", test_case);
    return printf("%lld\n", ans), void();
}
auto main() -> decltype(0) {
    freopen("poker.in", "r", stdin);
    freopen("poker.out", "w", stdout);
    scanf("%lld", &T);
    while (T--) Solve(++ Case);
    return 0;
}
/*
4
5
2 2
3 1
5 2
7 1
11 1
1
17 2
2
2 2
3 1
1
2 7
*/