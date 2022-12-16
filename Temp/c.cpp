#include <bits/stdc++.h>
static constexpr int N = 5e5 + 5, P = 1e9 + 7;
int n, ans, sum;
int a[N], b[N], cnt[N], phi[N], prime[N];
bool vis[N];
std::vector<int> factor[N];
void init(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++ prime[0]] = i, phi[i] = i - 1;
        for (int j = 1; 1ll * i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = true;
            if (!(i % prime[j])) {phi[i * prime[j]] = phi[i] * prime[j]; break;}
            else phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j * j <= i; ++j)
            if (i % j == 0) {
                factor[i].emplace_back(j);
                if (i / j != j) factor[i].emplace_back(i / j);
            }
}
int inc(int x, int y) {return (x + y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
void add(int x) {sum = inc(sum, mul(mul(cnt[x], cnt[x]), phi[x]));}
void del(int x) {sum = inc(sum, P - mul(mul(cnt[x], cnt[x]), phi[x]));}
signed main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%d", &n); init(N - 1);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) {
        int m = 0;
        for (int j = i; j <= n; j += i) b[++ m] = a[j];
        for (int j = 1; j <= m; ++j)
            for (auto k : factor[b[j]])
                del(k), ++ cnt[k], add(k);
        ans = inc(ans, mul(sum, phi[i]));
        for (int j = 1; j <= m; ++j)
            for (auto k : factor[b[j]])
                del(k), -- cnt[k], add(k);
    }
    printf("%d\n", ans);
}