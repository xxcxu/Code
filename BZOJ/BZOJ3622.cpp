#include <bits/stdc++.h>
static constexpr int N = 223, R = 135;
int n, r, d[N];
double p[N], fp[N], Pow[N][N], f[N][R];
auto Init() -> void {
	for (int i = 1; i <= n; ++i) {
		Pow[i][0] = 1;
		for (int j = 1; j <= r; ++j)
			Pow[i][j] = Pow[i][j - 1] * (1 - p[i]);
	}
}
auto Calc() -> double {
	std::memset(f, 0, sizeof f);
	std::memset(fp, 0, sizeof fp);
	f[1][0] = Pow[1][r];
	f[1][1] = fp[1] = 1 - f[1][0];
	for (int i = 2; i <= n; ++i)
		for (int j = 0; j <= r; ++j) {
			fp[i] += f[i - 1][j] * (1 - Pow[i][r - j]);
			f[i][j] += f[i - 1][j] * Pow[i][r - j];
			if (j)
				f[i][j] += f[i - 1][j - 1] * (1 - Pow[i][r - j + 1]);
		}
	double ans = 0.0;
	for (int i = 1; i <= n; ++i)
		ans += d[i] * fp[i];
	return ans;
}
auto Solve(int test_case = 0) -> void {
	scanf("%d%d", &n, &r);
	for (int i = 1; i <= n; ++i)
		scanf("%lf%d", p + i, d + i);
	Init();
	printf("%.10lf\n", Calc());
}
auto main() -> decltype(0) {
	int t; scanf("%d", &t);
	while (t--) Solve();
}