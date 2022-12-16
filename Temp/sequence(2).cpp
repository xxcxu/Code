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
static constexpr int N = 5e3 + 5;
int n, m, ans;
int a[N], b[N], c[N];
int dp[N][N];
void cmax(int &x, int y) {if (y > x) x = y;}
signed main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
    read(n, m); m += n;
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) read(b[i]);
    for (int i = 1; i <= m; ++i) read(c[i]);
    std::memset(dp, -0x3f, sizeof dp);
    for (int i = 0; i <= m; ++i) dp[i][0] = 0;
    for (int i = n; i >= 1; --i) {
        for (int j = n - 1; j >= 0; --j)
            cmax(dp[a[i]][j + 1], dp[a[i]][j] - b[i] + c[a[i]]);
        for (int k = a[i]; k <= a[i] + 20; ++k)
            for (int j = 0; j <= n; ++j)
                cmax(dp[k + 1][j / 2], dp[k][j] + (j / 2) * c[k + 1]);
        for (int j = 1; j <= m; ++j) cmax(dp[j][0], dp[j - 1][0]); 
    }
    printf("%d\n", dp[m][0]);
	return 0;
}