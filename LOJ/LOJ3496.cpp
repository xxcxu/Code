#include <bits/stdc++.h>
#define eb emplace_back
using pii = std::pair<int, int>;
static const int N = 200005;
int n, m, k, a[N], l[N], r[N], f[N][32];
std::vector<int> b[N];
int calc(int l, int r) {
    int ans = 0;
    for (int i = 25; i >= 0; --i)
        if (f[l][i] <= r) l = f[l][i], ans += (1 << i);
    return ans;
}
signed main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d%d", l + i, r + i);
    for (int i = 1; i <= n; ++i) a[++ m] = l[i], a[++ m] = r[i];
    std::sort(a + 1, a + m + 1);
    m = std::unique(a + 1, a + m + 1) - a - 1;
    for (int i = 1; i <= n; ++i) {
        l[i] = std::lower_bound(a + 1, a + m + 1, l[i]) - a;
        r[i] = std::lower_bound(a + 1, a + m + 1, r[i]) - a;
        b[l[i]].eb(r[i]);
    }
	for (int i = m + 1, R = m + 1; i >= 1; --i) {
        for (int j : b[i]) R = std::min(R, j);
        f[i][0] = R;
    }
    for (int j = 1; j <= 25; ++j)
        for (int i = 1; i <= m + 1; ++i)
            f[i][j] = f[f[i][j - 1]][j - 1];
    if (calc(1, m) < k) return puts("-1"), 0;
    std::multiset<pii> s;
    s.emplace(1, 1); s.emplace(m, m);
    int ans = calc(1, m);
	for (int i = 1; k; ++i) {
        auto it = s.insert({l[i], r[i]});
        int L = std::prev(it) -> second;
        int R = std::next(it) -> first;
        if (l[i] < L || R < r[i]) {s.erase(it); continue;}
        int v = calc(L, l[i]) + calc(r[i], R) - calc(L, R);
        if (ans + v >= k - 1) -- k, ans += v, printf("%d\n", i);
        else s.erase(it);
    }
	return 0;
}