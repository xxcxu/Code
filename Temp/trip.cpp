#include <bits/stdc++.h>
using ll = long long;
using i128 = __int128_t;
static constexpr int N = 2e5 + 5; 
int n, cnt, pri[N]; ll pre[N], suf[N], b[N], c[N];
bool vis[N];
ll gcd(ll x, ll y) {return !y ? x : gcd(y, x % y);}
void init(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) pri[++ cnt] = i;
        for (int j = 1; i * pri[j] <= n; ++j) {
            vis[i * pri[j]] = true;
            if (!(i % pri[j])) break;
        }
    } return void();
}
int calc(int m) {
    i128 res = 1;
    for (int i = 1; i <= m; ++i) res *= pri[i];
    int max = m;
    for (int i = 1; i <= n; ++i) c[i] = b[i];
    for (int i = 1; i <= n; ++i) {
        int p = m; i128 ret = res;
        ret /= (i > m ? 1 : pri[m - i + 1]);
        while (p >= 1 && c[i] < ret) {
            if (p == m - i + 1) {-- p; continue;}
            ret /= pri[p --];
        }
        c[i] = ret;
        if (p == m - i) ++ p;
        max = std::min(max, p);
    }
    pre[1] = c[1];
    for (int i = 2; i <= n; ++i) pre[i] = gcd(pre[i - 1], c[i]);
    suf[n] = c[n];
    for (int i = n - 1; i >= 1; --i) suf[i] = gcd(suf[i + 1], c[i]);
    for (int i = 1; i <= n; ++i) if (gcd(pre[i - 1], suf[i + 1]) == 1) return max + 1;
    return max;
}
signed main() {
    freopen("trip.in", "r", stdin);
    freopen("trip.out", "w", stdout);
    init(100);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", b + i);
    std::sort(b + 1, b + n + 1);
    int ans = 0;
    for (int i = 1; i <= n && i <= 17; ++i) ans = std::max(ans, calc(i));
    printf("%d\n", ans);
    return 0;
}