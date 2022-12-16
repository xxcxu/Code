#include <bits/stdc++.h>
#define int long long
using pii = std::pair<int, int>;
static constexpr int N = 1e3 + 5;
int n, m, k, cnt, lcp[N][N], dp[N][N], d[N][N];
char s[N];
class Substr{public: int l, r;} a[N * N];
inline bool operator < (const Substr &a, const Substr &b) {
    int lcp = ::lcp[a.l][b.l];
    int len1 = a.r - a.l + 1, len2 = b.r - b.l + 1;
    if (lcp >= len1 || lcp >= len2) return len1 < len2;
    return s[a.l + lcp] < s[b.l + lcp];
}
auto check(int x) -> bool {
    std::memset(dp, 0, sizeof dp);
    std::memset(d, 0, sizeof d);
    d[n + 1][0] = 1;
    int glen = a[x].r - a[x].l + 1;
    for (int i = n; i; --i) {
        int t = std::min(glen, ::lcp[a[x].l][i]);
        if (t == glen || s[i + t] > s[a[x].l + t])
            for (int j = 1; j <= m; ++j)
                dp[i][j] = d[i + t + 1][j - 1];
        for (int j = 0; j <= m; ++j)
            d[i][j] = std::min(d[i + 1][j] + dp[i][j], k);
    } return dp[1][m] >= k;
}
auto main() -> decltype(0) {
    scanf("%lld%lld%lld%s", &n, &m, &k, s + 1);
    for (int i = n; i; --i)
        for (int j = n; j; --j)
            if (s[i] == s[j]) ::lcp[i][j] = ::lcp[i + 1][j + 1] + 1;
            else ::lcp[i][j] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            a[++ cnt] = (Substr){i, j};
    std::sort(a + 1, a + cnt + 1);
    int l = 1, r = cnt;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }
    for (int i = a[l].l; i <= a[l].r; ++i) putchar(s[i]);
    return puts(""), 0;
}