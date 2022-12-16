#include <bits/stdc++.h>
static constexpr int N = 2e5 + 5;
int n, ans, p[N], d[N], cnt[N];
auto prev(int x) -> int {return !x ? n - 1 : x - 1;}
auto next(int x) -> int {return x == n - 1 ? 0 : x + 1;}
auto calc(int x) -> int {
    if (p[x] == x) return 0;
    if (p[x] > x) return p[x] - x;
    if (p[x] < x) return n - (x - p[x]);
}
auto main() -> decltype(0) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", p + i), ++ p[i];
    for (int i = 1; i <= n; ++i) d[i] = calc(i);
    for (int i = 1; i <= n; ++i) ++ cnt[d[i]], ++ cnt[prev(d[i])], ++ cnt[next(d[i])];
    for (int i = 1; i <= n; ++i) ans = std::max(ans, cnt[i]);
    return printf("%d\n", ans), 0;
}