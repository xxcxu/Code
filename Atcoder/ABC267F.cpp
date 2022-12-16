#include <bits/stdc++.h>
using pii = std::pair<int, int>;
static constexpr int N = 2e5 + 5;
int n, q, end, path[N], dis[N], ans[N];
std::vector<int> e[N];
std::vector<pii> qy[N];
void Dfs(int x, int fa) {
    for (int y : e[x])
    	if (y ^ fa) {
	        dis[y] = dis[x] + 1;
	        Dfs(y, x);
    	}
}
void Dfs2(int x, int fa) {
    for (auto ask : qy[x]) {
        int id = ask.first, k = ask.second;
        if (k <= end) ans[id] = path[end - k + 1];
    }
    path[++ end] = x;
    for (int y : e[x]) if (y ^ fa) Dfs2(y, x);
    -- end;
}
int Calc(int s) {
	static int root;
	dis[root = s] = 0;
	Dfs(root, root);
    return std::max_element(dis + 1, dis + n + 1) - dis;
}
int main() {
	scanf("%d", &n);
	std::memset(ans, -1, sizeof ans);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	scanf("%d", &q);
	for (int i = 1, x, k; i <= q; ++i) {
		scanf("%d%d", &x, &k);
		qy[x].emplace_back(i, k);
	}
    int l = Calc(1), r = Calc(l);
    Dfs2(l, l); Dfs2(r, r);
    for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
    return 0;
}