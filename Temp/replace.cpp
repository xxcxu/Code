#include <bits/stdc++.h>
#define ub upper_bound
static constexpr int N = 1e6 + 5;
int n, m, k;
int a[N], b[N], c[N], d[N], dp[N], tr[N << 1];
#define ls (x << 1)
#define rs (ls | 1)
void cmin(int &x, int y) {x = std::min(x, y);}
void direct() {
    for (int i = 1; i <= n; ++i) c[i] = a[i];
    for (int i = 1; i <= m; ++i) c[i + n] = b[i];
    std::sort(b + 1, b + m + 1);
    std::sort(c + 1, c + n + m + 1);
    k = std::unique(c + 1, c + n + m + 1) - c - 1;
    for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(c + 1, c + k + 1, a[i]) - c;
    for (int i = 1; i <= m; ++i) b[i] = std::lower_bound(c + 1, c + k + 1, b[i]) - c;
}
void add(int x, int y) {
    x += 1e6;
    for (; x < N * 2; x += x & -x) cmin(tr[x], y);
}
int ask(int x) {
    x += 1e6;
    int ans = n + 1;
    for (; x; x -= x & -x) cmin(ans, tr[x]);
    return ans;
}
signed main() {
    freopen("replace.in", "r", stdin);
    freopen("replace.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i); a[++ n] = 1e9 + 7;
    for (int i = 1; i <= m; ++i) scanf("%d", b + i);
    direct();
    std::memset(tr, 10, sizeof tr);
    for (int i = 1; i <= n; ++i) d[i] = std::ub(b + 1, b + m + 1, a[i]) - b - 1; // 0 ~ m
    d[n] = m;
    for (int i = 1; i <= n; ++i) {
        dp[i] = ask(d[i] - i + 1) + i - 1;
        if (a[i - 1] < a[i]) cmin(dp[i], dp[i - 1]);
        add(d[i - 1] - (i - 1), dp[i - 1] - (i - 1));
    }
    printf("%d\n", dp[n] > n ? -1 : dp[n]);
    return 0;
}