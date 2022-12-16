#include <bits/stdc++.h>
#define int long long 
static constexpr int N = 1e5 + 6;
int n, m, rt[N], a[N], fst[N];
std::set<int> s[N];
class SegmentTree {
	private: int cnt;
	private: class TreeNode {public: int lc, rc, w;} tr[N * 100];
	#define ls (tr[rt].lc)
	#define rs (tr[rt].rc)
	public: void Update(int &rt, int l, int r, int x, int w) {
		if (!rt) rt = ++ cnt;
		tr[rt].w += w;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (x <= mid) Update(ls, l, mid, x, w);
		else Update(rs, mid + 1, r, x, w);
	}
	public: int Query(int rt, int l, int r, int x) {
		if (!rt) return 0;
		if (l == r) return tr[rt].w;
		int mid = (l + r) >> 1;
		if (x <= mid) return Query(ls, l, mid, x) + tr[rs].w;
		else return Query(rs, mid + 1, r, x);
	}
	#undef ls
	#undef rs
} Tree;
class TreeArray {
	public: void Add(int x, int y, int w) {
		for (; x <= n; x += x & -x) Tree.Update(rt[x], 1, n, y, w);
	}
	public: int Ask(int x, int y) {
		int ans = 0;
		for (; y; y -= y & -y) ans += Tree.Query(rt[y], 1, n, x);
		return ans;
	}
} Bit;
void Update(int x, int y) {
	if (fst[x]) Bit.Add(x, fst[x], fst[x] - x);
	if (y) Bit.Add(x, y, x - y);
	fst[x] = y;
}
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
	for (int i = 1; i <= n; ++i) {
		if (s[a[i]].size())
			fst[i] = *s[a[i]].rbegin(),
			Bit.Add(i, fst[i], i - fst[i]);
		s[a[i]].insert(i);
	}
	for (int i = 1, opt, x, y; i <= m; ++i) {
		scanf("%lld%lld%lld", &opt, &x, &y);
		if (opt & 1) {
			auto it = s[a[x]].find(x);
			if (std::next(it) != s[a[x]].end())
				Update(*(std::next(it)), (it == s[a[x]].begin() ? 0 : *std::prev(it)));
			s[a[x]].erase(x);
			a[x] = y;
			s[y].insert(x);
			it = s[y].find(x);
			Update(x, (it == s[y].begin() ? 0 : *std::prev(it)));
			if (std::next(it) != s[y].end())
				Update(*(std::next(it)), x);
		} else printf("%lld\n", Bit.Ask(x, y));
	} return 0;
}
