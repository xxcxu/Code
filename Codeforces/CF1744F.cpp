#include <bits/stdc++.h>
#define int long long
const int N = 2e5 + 10;
int n, a[N], pos[N];
void solve() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for (int i = 1; i <= n; ++i) pos[a[i]] = i;
    int l = pos[0], r = pos[0];
    int ans = 1, cnt = 0;
    if (l > 1) ++ ans; if (r < n) ++ ans;
    for (int i = 1; i < n; ++i) {
        int next = pos[i];
        if (l <= next && next <= r) -- cnt;
        if (next < l) while (l > next) cnt += (a[-- l] > i);
        if (next > r) while (r < next) cnt += (a[++ r] > i);
        int small = r - l - cnt, greater = cnt;
        {
            int sum = small - greater;
            int left  = std::max(sum - (n - r), 0ll);
            int right = std::min(sum, l - 1);
            ans += std::max(right - left + 1, 0ll);
        }
        {
            int sum = small + 1 - greater;
            int left = std::max(sum - (n - r), 0ll);
            int right = std::min(sum, l - 1);
            ans += std::max(right - left + 1, 0ll);
        }
    } 
    printf("%lld\n", ans);
}
signed main() {
    int t; scanf("%lld", &t);
    while (t--) solve();
    return 0;
}
