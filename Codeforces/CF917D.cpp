#include <bits/stdc++.h>
#define int long long
const int N = 1e2 + 5, P = 1e9 + 7;
int Add(int x, int y) {return x + y >= P ? x + y - P : x + y;}
int n, g[N], h[N], size[N], dp[N][N][2], f[N][2], c[N][N], pown[N];
std::vector<int> e[N];
void Dfs(int x, int fa) {
	dp[x][1][0] = dp[x][1][1] = 1, size[x] = 1;
	for (int y : e[x]) if (y ^ fa) {
		Dfs(y, x);
		for (int j = 1; j <= size[x]; ++j)
			for (int k = 1; k <= size[y]; ++k) {
				f[j + k][0] = Add(f[j + k][0], dp[x][j][0] * dp[y][k][1] % P);
				f[j + k][1] = Add(f[j + k][1], dp[x][j][1] * dp[y][k][1] % P);
				f[j + k - 1][0] = Add(f[j + k - 1][0], dp[x][j][0] * dp[y][k][0] % P);
				f[j + k - 1][1] = Add(f[j + k - 1][1], Add(dp[x][j][1] * dp[y][k][0] % P, dp[x][j][0] * dp[y][k][1] % P));
			}
		size[x] += size[y];
		for (int j = 1; j <= size[x]; ++j)
			for (int k = 0; k <= 1; ++k)
				dp[x][j][k] = f[j][k], f[j][k] = 0;
	}
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%lld%lld", &u, &v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	Dfs(1, 0);
	for (int i = 0; i <= n; ++i) {
		c[i][0] = 1;
		for (int j = 1; j <= i; ++j) c[i][j] = Add(c[i - 1][j - 1], c[i - 1][j]);
	} 
	for (int i = pown[0] = 1; i <= n; ++i) pown[i] = pown[i - 1] * n % P;
	for (int i = 0; i < n - 1; ++i) g[i] = dp[1][n - i][1] * pown[n - i - 2] % P;
	g[n - 1] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			int res = c[j][i] * g[j] % P;
			h[i] = (h[i] + ((i - j & 1 ? -1 : 1) * res + P) % P) % P;
		}
		printf("%lld%c", h[i], " \n"[i == n - 1]);
	} return 0;
}