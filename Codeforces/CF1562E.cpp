#include <bits/stdc++.h>
static constexpr int N = 5e3 + 5;
int T, n, ans, Case;
char s[N];
int f[N], lcp[N][N];
auto Check(int i, int j) -> bool {
    int p = lcp[i][j];
    if (i + p - 1 >= n) return false;
    return s[i + p] > s[j + p];
}
auto Solve(int test_case = 0) -> void {
    scanf("%d%s", &n, s + 1);
    lcp[n + 1][n + 1] = ans = 0;
    for (int i = n; ~i; --i)
        for (int j = n; ~j; --j)
            lcp[i][j] = (s[i] == s[j] ? lcp[i + 1][j + 1] + 1 : 0);
    for (int i = 1; i <= n; ++i) {
        f[i] = n - i + 1;
        for (int j = 1; j < i; ++j)
            if (Check(i, j))
                f[i] = std::max(f[i], f[j] + n - i + 1 - lcp[i][j]);
        ans = std::max(ans, f[i]);
    }
    return printf("%d\n", ans), void();
}
auto main() -> decltype(0) {
    scanf("%d", &T);
    while (T--) Solve(++ Case);
    return 0;
}