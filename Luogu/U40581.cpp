#include <bits/stdc++.h>
#define int long long
#define eb emplace_back
static const int N = 100005;
struct TreeNode {
	int lc, rc, sum0, sum1, lmx0, lmx1, rmx0, rmx1;
} tr[N << 5];
int n, ans, cnt;
int rt[N];
std::vector<int> e[N];
#define ls(x) tr[x].lc
#define rs(x) tr[x].rc
void pushup(int x, int l, int r) {
	int mid = (l + r) >> 1;
	int Llen = mid - l + 1;
	int Rlen = r - mid;
	if (!ls(x)) tr[ls(x)].sum0 = Llen * (Llen + 1) / 2, tr[ls(x)].lmx0 = tr[ls(x)].rmx0 = Llen;
	if (!rs(x)) tr[rs(x)].sum0 = Rlen * (Rlen + 1) / 2, tr[rs(x)].lmx0 = tr[rs(x)].rmx0 = Rlen;
	tr[x].sum0 = tr[ls(x)].sum0 + tr[rs(x)].sum0 + tr[ls(x)].rmx0 * tr[rs(x)].lmx0;
	tr[x].sum1 = tr[ls(x)].sum1 + tr[rs(x)].sum1 + tr[ls(x)].rmx1 * tr[rs(x)].lmx1;
	tr[x].lmx0 = tr[ls(x)].lmx0 == Llen ? tr[ls(x)].lmx0 + tr[rs(x)].lmx0 : tr[ls(x)].lmx0;
	tr[x].lmx1 = tr[ls(x)].lmx1 == Llen ? tr[ls(x)].lmx1 + tr[rs(x)].lmx1 : tr[ls(x)].lmx1;
	tr[x].rmx0 = tr[rs(x)].rmx0 == Rlen ? tr[rs(x)].rmx0 + tr[ls(x)].rmx0 : tr[rs(x)].rmx0;
	tr[x].rmx1 = tr[rs(x)].rmx1 == Rlen ? tr[rs(x)].rmx1 + tr[ls(x)].rmx1 : tr[rs(x)].rmx1;
}
void insert(int &x, int l, int r, int p) {
	if (!x) x = ++ cnt;
	if (l == r) {
		tr[x].lmx1 = tr[x].rmx1 = tr[x].sum1 = 1;
		return void();
	}
	int mid = (l + r) >> 1;
	if (p <= mid) insert(ls(x), l, mid, p);	
	else insert(rs(x), mid + 1, r, p);
	pushup(x, l, r);
}	 
void merge(int &x, int y, int l, int r) {
	if (!x || !y) return x = x | y, void();
	if (l == r) return x = tr[x].sum1 ? x : y, void();
	int mid = (l + r) >> 1;
	merge(ls(x), ls(y), l, mid);
	merge(rs(x), rs(y), mid + 1, r);
	pushup(x, l, r);
}
void dfs(int x, int fa) {
	for (int y : e[x]) if (y != fa) {
		dfs(y, x);
		merge(rt[x], rt[y], 1, n);
	}
	insert(rt[x], 1, n, x);
	int res = n * (n + 1) / 2 - tr[rt[x]].sum0 - tr[rt[x]].sum1;
	if (x != 1) ans += res;
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i < n; ++i) {
		static int x, y;
		scanf("%lld%lld", &x, &y);
		e[x].eb(y); e[y].eb(x);
	}
	dfs(1, 0);
	return printf("%lld\n", ans), 0;
}