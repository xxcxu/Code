#include <bits/stdc++.h>
static constexpr int N = 2e5 + 5;
int n, k, a[N]; long long ans;
std::pair<int, int> b[N];
signed main() {
    freopen("rotate.in", "r", stdin);
    freopen("rotate.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[i] = std::pair<int, int>(a[i], i);
    std::sort(b + 1, b + n + 1);
    for (int i = n; i > n / 2; --i) ans += b[i].first;
    for (int i = 1; i <= n / 2; ++i) a[b[i].second] = 1;
    for (int i = n; i > n / 2; --i) a[b[i].second] = -1;
    int s = 0, min = 0;
    for (int i = 1; i <= n; ++i) {
        s += a[i];
        if (s < min) min = s, k = i;
    }
    printf("%d %lld\n", k, ans);
    return 0;
}