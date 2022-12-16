#include <bits/stdc++.h>

#define eb emplace_back
using pii = std::pair<int, int>;

static constexpr int N = 1e5 + 5;
int n, k, root, right, Clen;
int dp[N], fa[N], dep[N];
std::vector<pii> e[N];

void dfs(int x, int pre) {
	for (auto &it : e[x]) {
		int y = it.first;
		if (y == pre) continue;
		dep[y] = dep[x] + 1;
		fa[y] = x;
		dfs(y, x);
	}
}

void Change(int x) {
	while (fa[x]) {
		for (auto &it : e[x]) {
			int &y = it.first, &z = it.second;
			if (y == fa[x]) {z = -1; break;}
		}
		for (auto &it : e[fa[x]]) {
			int &y = it.first, &z = it.second;
			if (y == x) {z = -1; break;}
		}
		x = fa[x];
	}
}

void TreeDp(int x, int pre) {
	for (auto &it : e[x]) {
		int &y = it.first, &z = it.second;
		if (y == pre) continue;
		TreeDp(y, x);
		Clen = std::max(Clen, dp[x] + dp[y] + z);
		dp[x] = std::max(dp[x], dp[y] + z);
	}
}

void find() {
	dep[root = 1] = 0; dfs(root, 0);
	root = std::max_element(dep + 1, dep + n + 1) - dep;
	dep[root] = 0; dfs(root, 0);
	right = std::max_element(dep + 1, dep + n + 1) - dep;
}

signed main() {
	scanf("%d%d", &n, &k);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		e[u].eb(v, 1), e[v].eb(u, 1);
	}
	find();
	if (k == 1) 
		printf("%d\n", 2 * (n - 1) - dep[right] + 1);
	if (k == 2) {
		int Pathlen = dep[right];
		fa[root] = 0; Change(right);
		Clen = 0; TreeDp(1, 0);
		printf("%d\n", 2 * n - Pathlen - Clen);
	}
}
