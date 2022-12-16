#include <bits/stdc++.h>

#define eb emplace_back

static constexpr int N = 15e4 + 5;
int n, m, W, H, dist[N], vis[N];
std::vector<int> E[N];

class cc {
	public: int x, y, id;
	public: cc(int x = 0, int y = 0, int id = 0): x(x), y(y), id(id) {}
	public: bool operator < (cc a) const {return y == a.y ? id < a.id : y < a.y;}
} a[N];
class edge {
	public: int p, t, l, r, d, u;
	public: edge(int p = 0, int t = 0, int l = 0, int r = 0, int d = 0, int u = 0):
		p(p), t(t), l(l), r(r), d(d), u(u) {}
} e[N];
class node {
	public: int id, v;
	public: node(int id = 0, int v = 0): id(id), v(v) {}
	public: bool operator < (node a) const {return v > a.v;}
};

std::priority_queue<node> q;
std::queue<int> tag;

namespace segment_tree {
	std::set<cc> s[N << 2];
	#define ls (rt << 1)
	#define rs (rt << 1 | 1)
	void update(int rt, int l, int r, int v) {
		s[rt].emplace(a[v]);
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (a[v].x <= mid) update(ls, l, mid, v);
		else update(rs, mid + 1, r, v);
	}
	void delet(int rt, int l, int r, int v) {
		s[rt].erase(a[v]);
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (a[v].x <= mid) delet(ls, l, mid, v);
		else delet(rs, mid + 1, r, v);
	}
}

using namespace segment_tree;

void calc(int rt, int l, int r, int id, int v) {
	int ql = e[id].l, qr = e[id].r;
	if (r < ql) return; if (l > qr) return;
	if (ql <= l && r <= qr) {
		auto it = s[rt].lower_bound(cc(n + 1, e[id].d, 0));
		for (; it != s[rt].end() && it -> y <= e[id].u; ++ it) {
			dist[it -> id] = v;
			tag.emplace(it -> id);             
			for (auto it2 : E[it -> id]) q.emplace(it2, e[it2].t + v);
		}
		while (tag.size()) delet(1, 1, n, tag.front()), tag.pop();
		return;
	}
	int mid = (l + r) >> 1;
	calc(ls, l, mid, id, v);
	calc(rs, mid + 1, r, id, v);
}

signed main() {
	scanf("%d%d%d%d", &n, &m, &W, &H);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
		a[i].id = i;
		update(1, 1, n, i);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &e[i].p, &e[i].t);
		scanf("%d%d%d%d", &e[i].l, &e[i].r, &e[i].d, &e[i].u);
		E[e[i].p].eb(i);
	}
	e[0] = edge(0, 0, a[1].x, a[1].x, a[1].y, a[1].y);
	q.emplace(0, 0);
	while (q.size()) {
		auto t = q.top(); q.pop();
		if (vis[t.id]) continue;
		vis[t.id] = true;
		calc(1, 1, n, t.id, t.v);
 	}
	for (int i = 2; i <= n; ++i) printf("%d\n", dist[i]);
	return 0;
}