#include<bits/stdc++.h>
template<typename DataType>
DataType read() {
	DataType t = 0, f = 0;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
	for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
	return f ? ~t + 1 : t;
}
#define eb emplace_back
using pii = std::pair<int, int>;
static constexpr int N = 2e5 + 5, inf = 1e9;
int n, q, cnt;
int dep[N], l[N], r[N], qu[N];
int anc[N][25];
std::vector<int> e[N];
std::multiset<pii> s;
inline int lca(int x, int y) {
	if (x == y) return x;
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; ~i; --i)
		if (dep[anc[x][i]] >= dep[y])
			x = anc[x][i];
	if (x == y) return x;
	for (int i = 20; ~i; --i)
		if (anc[x][i] != anc[y][i])
			x = anc[x][i], y = anc[y][i];
	return anc[x][0];
}
inline int dis(int x, int y) {
	if (x < 0 || y < 0) return -inf;
	if (x == y) return 0;
	return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}
struct path{
	int x, y;
	friend path operator + (path a, path b) {
		int x = -1, y = -1, d = -inf;
		auto check = [&](int a, int b) -> void {
			int dd = dis(a, b);
			if (dd > d) d = dd, x = a, y = b;
		};
		check(a.x, a.y); check(b.x, b.y);
		check(a.x, b.x); check(a.x, b.y);
		check(a.y, b.x); check(a.y, b.y);
		return (path){x, y};
	}
};
inline void dfs(int x, int pre) {
	static int time_stamp = 0;
	l[x] = ++ time_stamp;
	qu[time_stamp] = x;
	dep[x] = dep[pre] + 1;
	anc[x][0] = pre;
	for (auto &y : e[x]) {
		if (y == pre) continue;
		dfs(y, x);
	}
	r[x] = time_stamp;
}
class TreeArray {
	#define lowbit(x) ((x)&(-x))
	private: int s[N];
	public: inline void add(int x, int v) {for (; x <= n; x += lowbit(x)) s[x] += v;}
	public: inline int query(int x) {int ans = 0; for (; x; x -= lowbit(x)) ans += s[x]; return ans;}
	public: inline int query(int l, int r) {return query(r) - query(l - 1);}
} tree1;
class SegmentTree {
	#define ls (rt << 1)
	#define rs (rt << 1 | 1)
	private: int sum[N];
	private: path tr[N << 2];
	public: inline void pushup(int rt) {tr[rt] = tr[ls] + tr[rs];}
	public: inline void build(int rt, int l, int r) {
		tr[rt] = (path){-1, -1};
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(ls, l, mid); build(rs, mid + 1, r); 
	}
	public: inline void update(int rt, int l, int r, int x, int opt) {
		if (l == r) {
			if (opt == 1) tr[rt] = (path){qu[l], qu[l]};
			if (opt == -1) tr[rt] = (path){-1, -1};
			return;
		} 
		int mid = (l + r) >> 1;
		if (x <= mid) update(ls, l, mid, x, opt);
		else update(rs, mid + 1, r, x, opt);
		pushup(rt);
	}
	public: inline path query(int rt, int l, int r, int L, int R) {
		if (l == r) return tr[rt];
		int mid = (l + r) >> 1;
		if (L > mid) return query(rs, mid + 1, r, L, R);
		else if (R <= mid) return query(ls, l, mid, L, R);
		return query(ls, l, mid, L, R) + query(rs, mid + 1, r, L, R);
	}
	public: inline void add(int x) {if (!(sum[x]++)) update(1, 1, n, l[x], 1);}
	public: inline void del(int x) {if (!(--sum[x])) update(1, 1, n, l[x], -1);}
} tree2;
inline int jump(int x, int d) {
	if (dep[x] <= d) return 1;
	for (int i = 20; ~i; --i)
		if ((1 << i) <= d) d -= (1 << i), x = anc[x][i];
	return x;
}
inline int ask(int d) {
	int x = jump(s.rbegin() -> second, d);
	int u = jump(x, d);
	if (tree1.query(l[u], r[u]) != cnt) return false;
	path p = tree2.query(1, 1, n, l[u], r[u]);
	if (dis(x, p.x) <= d && dis(x, p.y) <= d) return true;
	return false;
}
signed main() {
	n = read<int>(), q = read<int>();
	for (int i = 1; i < n; ++i) {
		int u = read<int>(), v = read<int>();
		e[u].eb(v); e[v].eb(u);
	}
	dfs(1, 0); 
	tree2.build(1, 1, n);
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	for (int i = 1; i <= q; ++i) {
		int opt;
		opt = read<int>();
		if (opt == 1) {
			int u, v;
			u = read<int>(), v = read<int>();
			int L = lca(u, v);
			tree1.add(l[u], 1); tree1.add(l[v], 1);
			tree1.add(l[L], -1); tree2.add(L);
			++ cnt;
			s.emplace(dep[L], L);
		}
		if (opt == 2) {
			int u, v;
			u = read<int>(), v = read<int>();
			int L = lca(u, v);
			tree1.add(l[u], -1); tree1.add(l[v], -1);
			tree1.add(l[L], 1); tree2.del(L);
			-- cnt;
			s.erase(s.find(pii(dep[L], L)));
		}
		if (opt == 3) {
			int d;
			d = read<int>();
			puts(ask(d) ? "Yes" : "No");
		}
	} return 0;
}