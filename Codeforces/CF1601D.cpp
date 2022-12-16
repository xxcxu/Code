#include <bits/stdc++.h>
static constexpr int N = 5e5 + 5;
int n, d, ans;
class node {public: int s, a;} p[N];
signed main() {
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &p[i].s, &p[i].a);
    std::sort(p + 1, p + n + 1, [&](const node &a, const node &b) {
        int m1 = std::max(a.s, a.a);
        int m2 = std::max(b.s, b.a);
        return m1 == m2 ? a.s < b.s : m1 < m2;    
    });
    for (int i = 1; i <= n; ++i)
        if (p[i].s >= d) ++ ans, d = std::max(d, p[i].a);
    return printf("%d\n", ans), 0;
}    