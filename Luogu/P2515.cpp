#include <bits/stdc++.h>
const int N = 5e2 + 5;
int n, m, scc_cnt, w[N], v[N], d[N], dfn[N], bel[N], wei[N], val[N], indeg[N], f[N][N];
std::vector<int> Graph[N], Edge[N];

void tarjan(int x) {
	static int time_stamp = 0, top = 0;
	static int low[N], stack[N], instack[N];
	dfn[x] = low[x] = ++ time_stamp;
	stack[++ top] = x; instack[x] = true;
	for (auto y : Graph[x])
		if (!dfn[y]) tarjan(y), low[x] = std::min(low[x], low[y]);
		else if (instack[y]) low[x] = std::min(low[x], dfn[y]);
	if (dfn[x] == low[x]) {
		++ scc_cnt; int u;
		do {
			u = stack[top --];
			instack[u] = false;
			bel[u] = scc_cnt;
			wei[scc_cnt] += w[u];
			val[scc_cnt] += v[u];
		} while (u != x);
	} return void();
}
void Dfs(int x, int fa) {
    for(int i = wei[x]; i <= m; i++) f[x][i] = val[x];
	for (auto y : Edge[x]) {
		if (y == fa) continue;
        Dfs(y, x);
		for (int i = m; i >= wei[x]; --i)
			for (int j = 0; j <= i - wei[x]; ++j)
				f[x][i] = std::max(f[x][i], f[y][j] + f[x][i - j]);
	} return void();
}
signed main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", w + i);
	for (int i = 1; i <= n; ++i) scanf("%d", v + i);
	for (int i = 1; i <= n; ++i) scanf("%d", d + i), Graph[d[i]].emplace_back(i);
	for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; ++i)
		for (auto j : Graph[i]) if (bel[i] != bel[j]) Edge[bel[i]].emplace_back(bel[j]), ++ indeg[bel[j]];
	for (int i = 1; i <= scc_cnt; ++i) if (!indeg[i]) Edge[0].emplace_back(i);
	Dfs(0, -1);
	return printf("%d\n", f[0][m]), 0;
}