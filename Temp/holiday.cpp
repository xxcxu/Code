#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define eb emplace_back
using ll = long long;
static constexpr int N = 25e2 + 5;
int n, m, K; ll ans, val[N];
int dis[N][N]; bool vis[N][N];
std::vector<int> e[N], dp[N];
void bfs(int sx) {
	static std::queue<int> q;
    q.emplace(sx); dis[sx][sx] = 0; vis[sx][sx] = true;
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int v : e[u]) {
			if (vis[sx][v]) continue;
			vis[sx][v] = true;
			dis[sx][v] = dis[sx][u] + 1;
			q.emplace(v);
		}
	}
}
signed main() {
    scanf("%d%d%d", &n, &m, &K); ++ K;
    for (int i = 2; i <= n; ++i) scanf("%lld", val + i);
    for (int i = 1; i <= n; ++i) std::memset(dis[i], 0x3f, sizeof dis[i]);
    for (int i = 1; i <= m; ++i) {
    	static int u, v;
    	scanf("%d%d", &u, &v);
		e[u].eb(v); e[v].eb(u);
	}
	for (int i = 1; i <= n; ++i) bfs(i);
	for (int i = 2; i <= n; ++i)
		for (int j = 2; j <= n; ++j)
			if (dis[1][j] <= K && dis[j][i] <= K && i != j)
				dp[i].emplace_back(j);
 	for (int i = 2; i <= n; ++i) std::sort(all(dp[i]), [&](int a, int b) {return val[a] > val[b];});
 	for (int i = 2; i <= n; ++i) dp[i].resize(3);
    for (int i = 2; i <= n; ++i)
    	for (int j = 2; j <= n; ++j)
    		if (dis[i][j] <= K && i != j)
    			for (int a = 0; a < 3; ++a)
    				for (int b = 0; b < 3; ++b) {
    					static int x, y;
						x = dp[i][a], y = dp[j][b];
    					if (!x || !y || x == j || y == i || x == y) continue;
    					ans = std::max(ans, val[i] + val[j] + val[x] + val[y]);
					}
	return printf("%lld\n", ans), 0;
}