#include <bits/stdc++.h>
#define int long long
static constexpr int N = 1e3 + 5, M = 1e4 + 5, P = 998244353;
int n, m, K, ans, p[N], inv[M], f[11][M];
auto Inc(int x, int y) -> int {return x + y >= P ? (x + y - P) : x + y;}
auto main() -> decltype(0) {
	scanf("%lld%lld%lld", &n, &K, &m); inv[1] = 1; K = n - K + 1;
	for (int i = 2; i <= m; ++i) inv[i] = inv[P % i] * (P - P / i) % P;
	for (int i = 1; i <= K; ++i) f[i][0] = -1;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", p + i);
		for (int j = m; j >= p[i]; --j)
			for (int k = K; k; --k)
				f[k][j] = Inc(f[k][j], Inc(f[k - 1][j - p[i]], P - f[k][j - p[i]]));
	}
	for (int i = 1; i <= m; ++i) ans = Inc(ans, f[K][i] * inv[i] % P);
	return printf("%lld\n", ans * m % P), 0;
}