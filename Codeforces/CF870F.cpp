#include <bits/stdc++.h>
using ll = long long;
static const int N = 1e7 + 5;
int n, cnt; ll ans, ans0, ans1, ans2, ans3;
int a[N], c[N], p[N], prime[N];
ll phi[N]; bool vis[N];
void sieve(int n) {
    phi[1] = 1; vis[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++ cnt] = i, p[i] = i, phi[i] = i - 1;
        for (int j = 1; 1ll * i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = true;
            p[i * prime[j]] = prime[j];
            phi[i * prime[j]] = phi[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
            if (i % prime[j] == 0) break;
        }
    }
}
ll ask(int l, int r) {return l > r ? 0 : c[r] - c[l - 1];}
signed main() {
    scanf("%d", &n); sieve(n);
    for (int i = 1; i <= n; ++i) phi[i] += phi[i - 1];
    for (int i = 2; i <= n; ++i) ++ a[p[i]];
    for (int i = 1; i <= n; ++i) c[i] += c[i - 1] + a[i];
    ans1 = 1ll * (n - 1) * (n - 2) / 2 + n - phi[n];
    for (int i = 1; i <= cnt; ++i) {
        int x = prime[i];
        int l = std::max(x, n / x) + 1, r = n / 2;
        ans3 += ask(l, r) * a[x];
    }
    for (int i = 1; i <= cnt; ++i) {
        int x = prime[i];
        int l = std::max(x, n / 2) + 1, r = n;
        ans0 += ask(l, r) * a[x];
    }
    ans2 = 1ll * (n - 1) * (n - 2) / 2 - ans0 - ans1 - ans3;
    ans = 0 * ans0 + 1 * ans1 + 2 * ans2 + 3 * ans3;
    return printf("%lld\n", ans), 0; 
}