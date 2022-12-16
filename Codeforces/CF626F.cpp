#include <bits/stdc++.h>
const int N = 5e2 + 5, mod = 1e9 + 7;
int Rev(int x) {return (x % mod + mod) % mod;}
int Add(int x, int y) {x = Rev(x), y = Rev(y); return (x + y) % mod;}
void cAdd(int &x, int y) {x = Add(x, y);}
int Mul(int x, int y) {x = Rev(x), y = Rev(y); return 1ll * x * y % mod;}
void cMul(int &x, int y) {x = Mul(x, y);}
int n, m, a[N], dp[2][N][N << 1];
signed main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", a + i);
	std::sort(a + 1, a + 1 + n); dp[0][0][0] = 1;
	for(int i = 0; i < n; i ++) {
		int now = i & 1;
		memset(dp[now ^ 1], 0, sizeof dp[now ^ 1]);
		for(int j = 0; j <= n; j ++)
			for(int k = 0; k <= m; k ++) {
				int next = k; cAdd(next, 1ll * (a[i + 1] - a[i]) * j);
                if (next > m || !dp[now][j][k]) continue;
                cAdd(dp[now ^ 1][j + 1][next], dp[now][j][k]);
                if (j) cAdd(dp[now ^ 1][j - 1][next], Mul(dp[now][j][k], j));
                cAdd(dp[now ^ 1][j][next], Mul(dp[now][j][k], j + 1));
			}   
	} int ans = 0;
    for (int i = 0; i <= m; ++i) cAdd(ans, dp[n & 1][0][i]);
    return printf("%d\n", ans), 0;
}