#include <bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read() {
	ll s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') w = -1; c = getchar();}
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar();
	return s * w;
}
const int N = 31, INF = 2e9, M = 500010;
const int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};
const int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};
int m, n, a[N][N], st, ed;
inline int getid(int x, int y) {
	return (x - 1) * m + y;
}
int last[N * N], cnt;
struct edge {
	int to, next;
} e[M];
void addedge(int x, int y) {
	e[++cnt].to = y;
	e[cnt].next = last[x];
	last[x] = cnt;
}
bool vis[N * N];
void dfs(int id, int x, int y) {
	vis[getid(x, y)] = 1;
	for (int i = 0; i < 8; i++) {
		int sx = x + dx[i], sy = y + dy[i], sid = getid(sx, sy);
		if (sx < 1 || sx > n || sy < 1 || sy > m) continue;
		if (vis[sid]) continue;
		if (a[sx][sy] == 1) dfs(id, sx, sy);
		else vis[sid] = 1, addedge(id, sid);
	}
}
queue <int> q;
int dis[N * N];
ll f[N * N];
void spfa() {
	memset(vis, 0, sizeof(vis));
	std::memset(dis, 0x3f, sizeof dis);
	dis[st] = 0, f[st] = 1, vis[st] = 1;
	q.push(st);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		vis[x] = 0;
		for (int i = last[x]; i; i = e[i].next) {
			int v = e[i].to;
			if (dis[v] > dis[x] + 1) {
				dis[v] = dis[x] + 1;
				f[v] = f[x];
				if (!vis[v]) q.push(v), vis[v] = 1;
			}
			else if (dis[v] == dis[x] + 1) f[v] += f[x];
		}
	}
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			a[i][j] = read();
			if (a[i][j] == 3) st = getid(i, j);
			if (a[i][j] == 4) ed = getid(i, j);
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == 0 || a[i][j] == 3) {
				memset(vis, 0, sizeof(vis));
				dfs(getid(i, j), i, j);
			}
		}
	spfa();
	if (dis[ed] != 0x3f3f3f3f) printf("%d\n%lld\n", dis[ed] - 1, f[ed]);
	else puts("-1");
	return 0;
}
