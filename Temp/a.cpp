#include <bits/stdc++.h>
static constexpr int N = 1e7 + 5;
int n, cnt;
int prime[N];
bool vis[N];
int gcd(int x, int y) {return !y ? x : gcd(y, x % y);}
void init(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++ cnt] = i;
        for (int j = 1; 1ll * i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = true;
            if (!(i % prime[j])) break;
        }
    }
}
void solve() {
    scanf("%d", &n);
    int d = 1;
    for (int i = 1; i <= cnt && prime[i] <= n; ++i)
        if (prime[i] > n / 2) ++ d;
    printf("%d\n", (n - d + 1) / 2 + d);
}
signed main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    init(N - 1);    
    int t; std::cin >> t;
    while (t--) solve();
    return 0;
}