#include <bits/stdc++.h>
static const int N = 200005;
int n, L, R, k;
int a[N], l[N], r[N], ans[N];
signed main() {
    scanf("%d%d%d%d", &n, &L, &R, &k);
    l[1] = L, r[1] = R;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 2; i <= n; ++i) {
        if (a[i] == a[i - 1]) l[i] = l[i - 1], r[i] = r[i - 1];
        if (a[i] >  a[i - 1]) l[i] = l[i - 1] + 1, r[i] = std::min(r[i - 1] + k, R);
        if (a[i] <  a[i - 1]) l[i] = std::max(l[i - 1] - k, L), r[i] = r[i - 1] - 1;
        if (l[i] > r[i]) return puts("-1"), 0;
        if (r[i] < L) return puts("-1"), 0;
        if (l[i] > R) return puts("-1"), 0;
    }
    ans[n] = l[n];
    for (int i = n - 1; i >= 1; --i) {
        if (a[i] == a[i + 1]) ans[i] = ans[i + 1];
        if (a[i] <  a[i + 1]) ans[i] = std::max(ans[i + 1] - k, l[i]);
        if (a[i] >  a[i + 1]) ans[i] = std::max(ans[i + 1] + 1, l[i]);
    }
    for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
    return 0;
}