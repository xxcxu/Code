#include <bits/stdc++.h>
using ll = long long;
static constexpr int N = 1e6 + 5;
int n, p, a[N];
ll c1(int x) {return x;}
ll c2(int x) {if (x < 2) return 0; return 1ll * x * (x - 1) / 2;}
ll c3(int x) {if (x < 3) return 0; return 1ll * x * (x - 1) * (x - 2) / 6;}
void solve() {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    std::sort(a + 1, a + n + 1, [&](int x, int y) {return x > y;});
    if (p == 1) {
        int p1, p2, p3;
        for (p1 = 4; p1 <= n; ++p1) if (a[p1] <= a[3] - n) break;
        for (p2 = 4; p2 <= n; ++p2) if (a[p2] <= a[2] - n) break;
        for (p3 = 4; p3 <= n; ++p3) if (a[p3] <= a[1] - n) break;
        p1 --; p2 --; p3 --;                               
        ll ans = c1(p1 - 3) + c2(p2 - 2) + c3(p3 - 1) + 1;
        printf("%lld\n", ans);
    }
    if (p == 2) {
        int p1, p2;
        for (p1 = 3; p1 <= n; ++p1) if (a[p1] <= a[2] - n) break;
        for (p2 = 4; p2 <= n; ++p2) if (a[p2] <= a[1] - n) break;
        p1 --; p2 --;
        ll ans = c1(p1 - 2) + c2(p1 - 2) + c3(p2 - 1);
        printf("%lld\n", ans);
    }
}
signed main() {
    freopen("T.in", "r", stdin);
    freopen("T.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();    
    return 0;
}