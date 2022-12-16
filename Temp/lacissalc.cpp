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
static constexpr int N = 70, M = 5e3 + 5, P = 998244353;
int n, k, t;
int c[N][N];
int dp[N][N][M];
signed main() {
    freopen("lacissalc.in", "r", stdin);
    freopen("lacissalc.out", "w", stdout);
    read(n, k, t);
    c[0][0] = 1;
    for (int i = 1; i <= n + 1; ++i) {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % P;
    }
    for (int i = 0; i <= n; ++i) dp[0][i][c[i + 1][2]] = 1;
    for (int i = 1; i < k; ++i)
        for (int to = 0; to <= n; ++to)
            for (int j = to; j <= n; ++j)
                for (int s = c[to][2]; s <= t; ++s)
                    dp[i][j][s] = (dp[i][j][s] + 1ll * c[j][to] * dp[i - 1][j - to][s - c[to][2]] % P) % P;   
    printf("%d\n", dp[k - 1][n][t]);
    return 0;
}