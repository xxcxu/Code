#include <bits/stdc++.h>

static constexpr int N = 3e2 + 5, P = 1e9 + 7;

int n, m, p, cnt;
int vis[N];
std::bitset<N> a, b[N];

int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
void insert(std::bitset<N> a) {
    for (int i = 1; i <= m; ++i)
        if (a[i]) {
            if (!vis[i]) ++ cnt, b[i] = a, vis[i] = 1;
            a ^= b[i];
            if (!a.count()) break;
        }
}
signed main() {
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        a.reset();   
        for (int j = 1, x; j <= m; ++j) scanf("%d", &x), a[j] = x;
        insert(a);
    }
    p = (qpow(2, n, P) + P - qpow(2, n - cnt, P)) % P;
    return printf("%lld\n", 1ll * p * qpow(2, m - 1, P) % P), 0;
}