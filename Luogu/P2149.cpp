#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
inline ll read() {
	ll s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') w = -1; c = getchar();}
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar();
	return s * w;
}
const int N = 1510, M = 300010;
int last[N], cnt, last2[N], cnt2;
struct edge {
	int to, next, w;
} e[M << 1], e2[M << 1];
void addedge(int x, int y, int w) {
	e[++cnt].to = y;
	e[cnt].next = last[x];
	e[cnt].w = w;
	last[x] = cnt;
}
int deg[N];
void addedge2(int x, int y, int w) {
	e2[++cnt2].to = y;
	e2[cnt2].next = last2[x];
	e2[cnt2].w = w;
	last2[x] = cnt2;
	deg[y]++;
}
int n, m, xa, ya, xb, yb;
int dis[5][N];
bool vis[N];
void dij(int id, int s) {
	priority_queue <pii, vector<pii>, greater<pii> > q; 
	memset(dis[id], 0x3f, sizeof(dis[id]));
	memset(vis, 0, sizeof(vis));
	q.push({0, s});
	dis[id][s] = 0;
	while (!q.empty()) {
		pii u = q.top(); q.pop();
		int pos = u.second;
		if (vis[pos]) continue;
		vis[pos] = 1;
		for (int j = last[pos]; j; j = e[j].next) {
			int v = e[j].to;
			if (dis[id][pos] + e[j].w < dis[id][v]) dis[id][v] = dis[id][pos] + e[j].w, q.push({dis[id][v], v});
		}
	}
}
int len[N], ans;
void topo() {
	queue <int> q;
	for (int i = 1; i <= n; i++)
		if (!deg[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = last2[u]; i; i = e2[i].next) {
			int v = e2[i].to;
			len[v] = max(len[v], len[u] + e2[i].w);
			deg[v]--;
			if (deg[v] == 0) q.push(v);
		}	
	}
	for (int i = 1; i <= n; i++) ans = max(ans, len[i]);
}
int main() {
	n = read(), m = read();
	xa = read(), ya = read(), xb = read(), yb = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		addedge(u, v, w), addedge(v, u, w);
	}
	dij(1, xa), dij(2, ya), dij(3, xb), dij(4, yb);
	for (int i = 1; i <= n; i++)
		for (int j = last[i]; j; j = e[j].next) 
			if (dis[1][i] + e[j].w + dis[2][e[j].to] == dis[1][ya]) 
				if (dis[3][i] + e[j].w + dis[4][e[j].to] == dis[3][yb])
					addedge2(i, e[j].to, e[j].w);
	topo();
	memset(last2, 0, sizeof(last2));
	cnt2 = 0;
	memset(deg, 0, sizeof(deg));
	memset(len, 0, sizeof(len));
	for (int i = 1; i <= n; i++)
		for (int j = last[i]; j; j = e[j].next)
			if (dis[1][i] + e[j].w + dis[2][e[j].to] == dis[1][ya])
				if (dis[4][i] + e[j].w + dis[3][e[j].to] == dis[3][yb])
					addedge2(i, e[j].to, e[j].w);
	topo();
	printf("%d\n", ans);
	return 0;
}