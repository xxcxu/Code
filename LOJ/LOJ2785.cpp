#include <bits/stdc++.h>
#define ls(i) ((i) << 1)
#define rs(i) ((i) << 1 | 1)
static const int N = 400010, inf = 1000000007;
int n, a[N], f[N][2];
int dfs(int i, int x) {
    if (x < std::min(a[ls(i)], a[rs(i)])) return i;
    if (x < a[ls(i)]) return std::min(dfs(ls(i), x), dfs(rs(i), x));
    if (x > a[ls(i)] && a[ls(i)] < a[rs(i)]) return dfs(ls(i), x);
    if (f[ls(i)][0] < f[ls(i)][1]) return dfs(rs(i), x);
    return dfs(ls(i), x);
}
signed main() {
    scanf("%d", &n);
    std::fill(a + 1, a + 2 * n + 5, inf);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = n; i >= 1; --i) {
        f[i][0] = dfs(i, a[i]);
        if (i + 1 & 1) f[i][1] = dfs(i | 1, a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        if (a[i] < std::min(a[ls(i)], a[rs(i)])) continue;
        if (a[i] > a[ls(i)] && a[ls(i)] < a[rs(i)]) {std::swap(a[i], a[ls(i)]); continue;}
        std::swap(a[i], a[rs(i)]);
        if (a[ls(i)] > a[rs(i)]) std::swap(a[ls(i)], a[rs(i)]);
        if (dfs(ls(i), a[ls(i)]) > dfs(rs(i), a[ls(i)])) std::swap(a[ls(i)], a[rs(i)]);
    }
    for (int i = 1; i <= n; ++i) printf("%d%c", a[i], " \n"[i == n]);
    return 0;
}