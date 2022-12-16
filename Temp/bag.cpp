#include <bits/stdc++.h>
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
static constexpr int N = 21, M = 51, inf = 1044266559;
int n, m;
int x[N], y[M];
int dp[M][1 << N];
void cmax(int &x, int y) {if (x < y) x = y;}
signed main() {
    freopen("bag.in", "r", stdin);
    freopen("bag.out", "w", stdout);
    read(n, m);
    for (int i = 1; i <= n; ++i) read(x[i]);
    for (int i = 1; i <= m; ++i) read(y[i]);
    std::sort(y + 1, y + m + 1);
    std::reverse(y + 1, y + m + 1);
    std::memset(dp, -0x3f, sizeof dp);
    for (int i = 1; i <= n; ++i) dp[i][0] = y[i];
    int R = (1 << n) - 1;
    for (int i = 1; i <= n; ++i) {
        for (int mask = 0; mask < 1 << n; ++mask)
            if (dp[i][mask] > -inf)
                for (int j = mask ^ R; j; j ^= (j & -j)) {
                    int k = __builtin_ctz(j & -j) + 1;
                    if (dp[i][mask] >= x[k]) cmax(dp[i][mask | (1 << k - 1)], dp[i][mask] - x[k]);
                    if (dp[i][mask] > -inf && y[i + 1] >= x[k]) cmax(dp[i + 1][mask | (1 << k - 1)], y[i + 1] - x[k]);
                }
        if (dp[i][R] > -inf) return printf("%d\n", i), 0;
    }
    puts("-1");
}