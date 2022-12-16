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
static constexpr int N = 3e2 + 5;
int n, m, P;
int dp[N][N][N];
void cadd(int &x, int y) {x = (x + y) % P;}
signed main() {
    read(n, m, P);
    dp[0][1][0] = 1;                   
    for (int i = 0; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = i; k >= 0; --k) {
                if (k) cadd(dp[i][j][k - 1], dp[i][j][k]);
                else cadd(dp[i][j + 1][i], dp[i][j][k]);
                cadd(dp[i + 1][j][k], 1ll * dp[i][j][k] * (k + 1) % P);
            }
    return printf("%d\n", dp[n][m][0]), 0;
}