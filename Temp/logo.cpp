#include <bits/stdc++.h>
static constexpr int N = 4e6 + 5;
int n, m, ans, p[N], l[N], r[N], L[N], R[N], next[N], s[2][N];
bool check(int x, int i, int j, int min, int max) {
    bool ret = true;
    if (min) ret &= (s[x][i - (j - min)] < s[x][i]);
    if (max) ret &= (s[x][i - (j - max)] > s[x][i]);
    return ret;
}
void init() {
    for (int i = 1; i <= n; ++i) l[i] = p[s[0][i] - 1], r[i] = p[s[0][i] + 1];
    for (int i = n; i >= 1; --i) {
        L[i] = l[i];
        R[i] = r[i];
        l[r[i]] = l[i];
        r[l[i]] = r[i];
    }
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j && !check(0, i, j + 1, L[j + 1], R[j + 1])) j = next[j];
        if (check(0, i, j + 1, L[j + 1], R[j + 1])) ++ j;
        next[i] = j;
    }
}
signed main() {
    freopen("logo.in", "r", stdin);
    freopen("logo.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", p + i), s[0][p[i]] = i;
    for (int i = 1; i <= m; ++i) scanf("%d", s[1] + i);
    init();
    for (int i = 1, j = 0; i <= m; ++i) {
        while (j && !check(1, i, j + 1, L[j + 1], R[j + 1])) j = next[j];
        if (check(1, i, j + 1, L[j + 1], R[j + 1])) ++ j;
        if (j == n) ++ ans, j = next[j];
    }
    return printf("%d\n", ans), 0;
}