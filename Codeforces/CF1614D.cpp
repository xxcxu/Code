#include <bits/stdc++.h>
#define eb emplace_back
using ll = long long;
static const int N = 100005, M = 20000000;
int n, a[N], cnt[M + 5];
ll dp[M + 5];
bool vis[M + 5];
std::vector<int> prime;
void sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime.eb(i);
        for (int j = 0; j < prime.size() && 1ll * i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}
signed main() {
    sieve(M + 1);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) ++ cnt[a[i]];
    int m = prime.size();
    for (int j = 0; j < m; ++j)
        for (int i = M / prime[j]; i >= 1; --i)
            cnt[i] += cnt[i * prime[j]];
    for (int i = M; i >= 1; --i) {
        dp[i] = 1ll * i * cnt[i];
        for (int j = 0; j < m && 1ll * i * prime[j] <= M; ++j)
            dp[i] = std::max(dp[i], dp[i * prime[j]] + 1ll * (cnt[i] - cnt[i * prime[j]]) * i);
    }
    return printf("%lld\n", dp[1]), 0;
}