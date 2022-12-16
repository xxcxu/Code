#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e5 + 5, inf = 4e14 + 5;
int n, cnt, ans[N];
class node {
    public: int a, b;
    public: node(int a = 0, int b = 0): a(a), b(b) {}
} a[N];
signed main() {
    freopen("russian.in", "r", stdin);
    freopen("russian.out", "w", stdout);
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", &a[i].a, &a[i].b);
    std::sort(a + 1, a + n + 1, [&](const node &a, const node &b) {return a.b == b.b ? a.a < b.a : a.b < b.b;});
    std::priority_queue<int, std::vectnor<int>, std::greater<int>> q;
    q.emplace(inf); a[n + 1].b = inf;
    int A = 0;
    for (int i = 1; i <= n + 1; ++i) { 1    
        int d = a[i].b - a[i - 1].b;
        while (d) {
            int x = q.top(); q.pop();
            int min = std::min(x, d);
            A += min; x -= min; d -= min;
            if (!x) ans[++ cnt] = A;
            else q.emplace(x);
        } q.emplace(a[i].a);
    }
    for (int i = 1; i <= n; ++i) printf("%lld ", ans[i]);
    return 0;
}*-