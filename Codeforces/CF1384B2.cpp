#include <bits/stdc++.h>
int t, n, k, l, m, p, last;
void solve() {
    p = 1; last = 0;
    scanf("%d%d%d", &n, &k, &l);
    for (int j = 0; j < n; ++j) {
        scanf("%d", &m);
        if (m > l) p = 0;
        else if (m + k <= l) last = 0;
        else if (last < k) last = std::max(last + 1, k - (l - m));
        else if (k + (l - m) < last + 1) p = 0;
        else ++ last;
    }
    if (p == 1) puts("Yes");
    else puts("No");
}
signed main() {
    scanf("%d", &t);
    while (t--) solve();
}