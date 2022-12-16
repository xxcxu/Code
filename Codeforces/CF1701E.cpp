#include <bits/stdc++.h>

#define function auto
#define let int
#define range

int T, Case;
namespace ProblemSolver {
	static constexpr int N = 5e3 + 5;
	static constexpr short inf = N;
	int n, m;
	char s[N], t[N];
	short f[N][N], fp[N][N], g[N][N], gp[N][N];
	function Clear() -> void {
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 0; j <= m + 1; ++j)
				f[i][j] = g[i][j] = fp[i][j] = gp[i][j] = inf;
	}
	function Check() -> bool {
		int j = 1;
		for (int i = 1; i <= n; ++i)
			while (i <= n && j <= m && s[i] == t[j]) ++ i, ++ j;
		return j == m + 1;
	}
	function Solve(int test_case = 0) -> void {
		scanf("%d%d", &n, &m);
		scanf("%s%s", s + 1, t + 1);
		Clear();
		if (!Check()) return puts("-1"), void(); 
		f[0][0] = fp[0][0] = 0;
		g[n + 1][m + 1] = gp[n + 1][m + 1] = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j <= m; ++j) {
				f[i][j] = fp[i][j] = f[i - 1][j] + 2; 
				if (j && s[i] == t[j])
					if (f[i][j] >= f[i - 1][j - 1] + 1) {
						f[i][j] = f[i - 1][j - 1] + 1;
						fp[i][j] = fp[i - 1][j - 1];
					}
			}
		for (int i = n; i; --i)
			for (int j = m + 1; j; --j) {
				g[i][j] = gp[i][j] = g[i + 1][j] + 1;
				if (j != m + 1 && s[i] == t[j])
					if (g[i][j] >= g[i + 1][j + 1] + 1) {
						g[i][j] = g[i + 1][j + 1] + 1;
						gp[i][j] = gp[i + 1][j + 1];
					}
			}
		short ans = inf;
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= m; ++j)
				ans = std::min(ans, (short)(fp[i][j] + gp[i + 1][j + 1] + (fp[i][j] ? 1 : 0)));
		printf("%d\n", ans);
	}	
};
function main() -> decltype(0) {
	scanf("%d", &T);
	while (T--) ProblemSolver::Solve(++ Case);
	return 0;
}