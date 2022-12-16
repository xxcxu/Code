#include <bits/stdc++.h>
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
using pii = std::pair<int, int>;
const int N = 4e2 + 5, mod = 998244353;
int n, m, dis[N][N], cnt[N][N];
std::vector<int> Graph[N];
void Bfs(int s, int *dis, int *cnt) {
    std::fill(dis + 1, dis + n + 1, 114514);
	dis[s] = 0; std::queue<int> q; q.emplace(s); cnt[s] = 1;
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int y : Graph[x]) 
			if (dis[y] > dis[x] + 1) dis[y] = dis[x] + 1, cnt[y] = cnt[x], q.emplace(y);
			else if (dis[y] == dis[x] + 1) cnt[y] = std::min(cnt[y] + cnt[x], 2);
    } return void();
}
int Calc(int x, int y) {
	int ans = 1;
	for (int i = 1; i <= n; ++i) {
        if (dis[i][x] + dis[i][y] == dis[x][y]) continue;
		int count = 0;
     	for (int j : Graph[i])
         	if (dis[j][x] + 1 == dis[i][x] && dis[j][y] + 1 == dis[i][y]) ++ count;
		ans = 1ll * ans * count % mod;
	} return ans;
}
signed main() {
    read(n, m);
    for (int i = 1, u, v; i <= m; ++i)
        read(u, v),
        Graph[u].emplace_back(v),
		Graph[v].emplace_back(u);
    for (int i = 1; i <= n; ++i) Bfs(i, dis[i], cnt[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        	if (cnt[i][j] == 2) printf("%d%c", 0, j == n ? '\n' : ' ');
			else printf("%d%c", Calc(i, j), j == n ? '\n' : ' ');
    return 0;
}
