#include <bits/stdc++.h>
using ll = long long;
static const int N = 400005, inf = 2e9;
int n; ll ans;
struct node {int a, b;} a[N];
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].a, &a[i].b);
    for (int i = 1; i <= n; ++i) if (a[i].a > a[i].b) std::swap(a[i].a, a[i].b);
    std::sort(a + 1, a + n + 1, [](node &a, node &b) {return a.a == b.a ? a.b > b.b : a.a > b.a;});
    for (int i = 1; i <= n; ++i) ans = std::max(ans, 1ll * a[i].a * a[i].b);
    for (int i = 1; i <= n; ++i) {
        static int max = 0;
        ans = std::max(ans, 2ll * a[i].a * std::min(max, a[i].b));
        max = std::max(max, a[i].b);
    }
    if (ans % 2 == 1) printf("%lld.5\n", ans / 2);
    else printf("%lld.0\n", ans / 2);
    return 0;
}