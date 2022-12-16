#include <bits/stdc++.h>
static constexpr int N = 5e2 + 5, P = 1024523;
int n, m, f[N][N], g[N][N];
char str[N], sub[N];
auto Inc(int &x, int y) -> void {x = (x + y >= P ? x + y - P : x + y);}
auto main() -> decltype(0) {
	scanf("%d%d%s%s", &n, &m, str + 1, sub + 1);
	f[0][0] = 1;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j)
			for (int k = 0; k <= i + j; ++k) {
				int l = i + j - k;
				if (str[i + 1] == str[k + 1]) Inc(g[j][k + 1], f[j][k]);
				if (str[i + 1] == sub[l + 1]) Inc(g[j][k], f[j][k]);
				if (sub[j + 1] == str[k + 1]) Inc(f[j + 1][k + 1], f[j][k]);
				if (sub[j + 1] == sub[l + 1]) Inc(f[j + 1][k], f[j][k]);
			}
		std::memcpy(f, g, sizeof g);
		std::memset(g, 0, sizeof g);
	}
	return printf("%d\n", f[m][n]), 0;
}