#include <bits/stdc++.h>
#define int long long
static const int N = 30005;
int n, k, sum, c[N];
bool check(int x) {
    int p = 0, now = 0;
    for (int i = 1; i <= n; ++i) {
        if ((now + c[i]) < x) now = 0;
        p += (now + c[i]) / x;
        now = (now + c[i]) % x;
    }
    return p >= k;
}
void solve() {
    scanf("%lld%lld", &n, &k); sum = 0;
    for (int i = 1; i <= n; ++i) scanf("%lld", c + i);
    for (int i = 1; i <= n; ++i) sum += c[i];
    if (sum < k) return puts("0"), void();
    int l = 1, r = sum / k, ans;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    return printf("%lld\n", k * ans), void();
}
signed main() {
    int t; scanf("%lld", &t);
    while (t--) solve();
    return 0;
}