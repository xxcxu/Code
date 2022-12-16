#include <bits/stdc++.h>
static constexpr int N = 505;
static constexpr double eps = 1e-12;
int n, m, k, s, t, d[N], e[N][N];
double p[N], a[N][N];
auto Id(int i, int j) -> int {return (i - 1) * n + j;}
auto Gauss(int n) -> void {
	for (int i = 1; i <= n; ++i) {
		int max = i;
		for (int j = i + 1; j <= n; ++j) if (a[max][i] < a[j][i]) max = j;
		std::swap(a[max], a[i]);
		if (std::fabs(a[i][i]) <= eps) return;
		for (int j = 1; j <= n; ++j) {
			if (i == j || std::fabs(a[j][i]) <= eps) continue;
			double t = a[j][i] / a[i][i];
			for (int k = i; k <= n + 1; ++k) a[j][k] -= a[i][k] * t;
		}
	} return;
}
auto main() -> decltype(0) {
	scanf("%d%d%d%d", &n, &m, &s, &t); k = n * n;
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		e[u][v] = e[v][u] = true;
		++ d[u]; ++ d[v];
	}
	for (int i = 1; i <= n; ++i) scanf("%lf", p + i);
	a[Id(s, t)][k + 1] = 1.0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			if (i ^ j)
				a[Id(i, j)][Id(i, j)] = 1 - p[i] * p[j];
			else
				a[Id(i, j)][Id(i, j)] = 1;
			for (int k = 1; k <= n; ++k)
				if (e[j][k] && (i ^ k))
					a[Id(i, j)][Id(i, k)] -= (1 - p[k]) / d[k] * p[i];
			for (int k = 1; k <= n; ++k)
				if (e[i][k] && (j ^ k))
					a[Id(i, j)][Id(k, j)] -= (1 - p[k]) / d[k] * p[j];
			for (int x = 1; x <= n; ++x)
				for (int y = 1; y <= n; ++y)
					if ((x ^ y) && e[i][x] && e[j][y])
						a[Id(i, j)][Id(x, y)] -= (1 - p[x]) * (1 - p[y]) / d[x] / d[y];
		}
	Gauss(k);
	for (int i = 1; i <= n; ++i)
		printf("%.10lf\n", a[Id(i, i)][k + 1] / a[Id(i, i)][Id(i, i)]);
	return 0;
}