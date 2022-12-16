#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e3 + 5, inf = 1e18;
int n, m, ans, a[N], f[N][N];
auto main() -> decltype(0) {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
	for (int i = 1; i <= m; ++i) f[0][i] = -inf;
	for (int i = 1; i <= n; ++i)	
		for (int j = 1; j <= m; ++j)
			f[i][j] = std::max(f[i - 1][j - 1] + a[i] * j, f[i - 1][j]);
	return printf("%lld\n", f[n][m]), 0;
}