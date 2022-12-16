#include <bits/stdc++.h>
const int N = 1e3 + 5, M = 1e5 + 5, K = 1e6 + 5, inf = 1e9 + 7;
int n, m, f[M], ans[K];
struct mall {int a, b, c;} a[N];
struct issue {int m, k, s, id;} q[K];
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d", &a[i].c, &a[i].a, &a[i].b);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) scanf("%d%d%d", &q[i].m, &q[i].k, &q[i].s), q[i].id = i;
    std::sort(a + 1, a + n + 1, [&](mall &a, mall &b) -> bool {return a.a < b.a;});
    std::sort(q + 1, q + m + 1, [&](issue &a, issue &b) -> bool {return a.m < b.m;});
    int top = 1; f[0] = inf;
    for (int i = 1; i <= m; ++i) {
        while (top <= n && a[top].a <= q[i].m) {
            for (int k = M - 5; k >= a[top].c; --k)
                f[k] = std::max(f[k], std::min(f[k - a[top].c], a[top].b));
            ++ top;
        } if (f[q[i].k] > q[i].m + q[i].s) ans[q[i].id] = true;
    }
    for (int i = 1; i <= m; ++i) puts(ans[i] ? "TAK" : "NIE");
    return 0;
}