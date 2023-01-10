#include <bits/stdc++.h>
#define int long long
static const int N = 100005;
int n, ans, a[N], cnt[N];
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for (int i = 1; i <= n; ++i) ++ cnt[a[i]];
    for (int i = 1; i <= n; ++i) ans += cnt[i] * i * (n - i + 1);
    for (int i = 1; i <  n; ++i) {
        int min = std::min(a[i], a[i + 1]);
        int max = std::max(a[i], a[i + 1]);
        ans -= min * (n - max + 1);
    }
    printf("%lld\n", ans);
    return 0;
}