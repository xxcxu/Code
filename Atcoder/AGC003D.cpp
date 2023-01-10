#include <bits/stdc++.h>
#define int long long
static const int N = 1e5 + 5;
int n, ans, cnt, a[N], b[N], c[N], prime[N];
bool vis[N];
std::map<int, int> map;
void sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++ cnt] = i;
        for (int j = 1; i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    } return void();
}
int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x *= x) if (y & 1) ans *= x;
    return ans;
}
signed main() {
    scanf("%lld", &n); sieve(5000);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for (int i = 1; i <= n; ++i) {
        int now = 1, res = 1;
        for (int j = 1; j <= cnt; ++j) {
            int exp = 0;
            while (a[i] % prime[j] == 0) {
                a[i] /= prime[j];
                ++ exp;
            }
            exp %= 3;
            if (exp) now *= qpow(prime[j], exp);
            if (exp) res *= qpow(prime[j], 3 - exp);
        }
        now *= a[i];
        res *= ((int)std::sqrt(a[i]) * (int)std::sqrt(a[i]) != a[i]) ? a[i] * a[i] : std::sqrt(a[i]);
        ++ map[now];
        b[i] = now, c[i] = res;
    }
    for (int i = 1; i <= n; ++i) {
        if (b[i] == 1) continue;
        ans += std::max(map[b[i]], map[c[i]]);
        map[b[i]] = map[c[i]] = 0;
    }
    ans += map[1] > 0;
    return printf("%lld\n", ans), 0;
}