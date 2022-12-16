#include <bits/stdc++.h>
using ll = long long;
static constexpr int N = 1e5 + 5, inf = 1e9 + 7;
static constexpr ll INF = 1ll * inf * inf;
int n, m, q;
int A[N], B[N];
#define ls (x << 1)
#define rs (x << 1 | 1)
struct node {
	int max1, max2, min1, min2;
	node(int max1 = -inf, int max2 = inf, int min1 = inf, int min2 = -inf):
		max1(max1), max2(max2), min1(min1), min2(min2) {}
	node operator + (const node &a) const {
		return node(
			std::max(max1, a.max1), std::min(max2, a.max2),
			std::min(min1, a.min1), std::max(min2, a.min2)
		);
	}
} c[N << 2], d[N << 2];
void build1(int x, int l, int r) {
	if (l == r) {
		if (A[l] >= 0) c[x].max1 = A[l], c[x].min1 = A[l];
		if (A[l] <= 0) c[x].max2 = A[l], c[x].min2 = A[l];
		return void();
	}
	int mid = (l + r) >> 1;
	build1(ls, l, mid); build1(rs, mid + 1, r);
	c[x] = c[ls] + c[rs];
}
void build2(int x, int l, int r) {
	if (l == r) {
		if (A[l] >= 0) d[x].max1 = B[l], d[x].min1 = B[l];
		if (A[l] <= 0) d[x].max2 = B[l], d[x].min2 = B[l];
		return void();
	}
	int mid = (l + r) >> 1;
	build2(ls, l, mid); build2(rs, mid + 1, r);
	d[x] = d[ls] + d[rs];
}
node query1(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return c[x];
	int mid = (l + r) >> 1; node ans = node();
	if (ql <= mid) ans = ans + query1(ls, l, mid, ql, qr);
	if (qr > mid) ans = ans + query1(rs, mid + 1, r, ql, qr);
	return ans;
}
node query2(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return d[x];
	int mid = (l + r) >> 1; node ans = node();
	if (ql <= mid) ans = ans + query2(ls, l, mid, ql, qr);
	if (qr > mid) ans = ans + query2(rs, mid + 1, r, ql, qr);
	return ans;
}
void cmin(ll &x, ll y) {if (y < x) x = y;}
signed main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; ++i) scanf("%d", &A[i]);
	for (int i = 1; i <= m; ++i) scanf("%d", &B[i]);
	build1(1, 1, n); build2(1, 1, m);
	while (q--) {
		static int l1, r1, l2, r2;
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		node a = query1(1, 1, n, l1, r1), b = query2(1, 1, m, l2, r2);
		ll ans1 = INF, ans2 = INF, ans3 = INF, ans4 = INF;
		
		if (a.max1 != -inf) {
			if (b.min1 != inf) cmin(ans1, 1ll * a.max1 * b.min1);
			if (b.max2 != inf) cmin(ans1, 1ll * a.max1 * b.max2);
		}
		if (a.max2 != inf) {
			if (b.max1 != -inf) cmin(ans2, 1ll * a.max2 * b.max1);
			if (b.min2 != -inf) cmin(ans2, 1ll * a.max2 * b.min2);
		}
		if (a.min1 != inf) {
			if (b.min1 != inf) cmin(ans3, 1ll * a.min1 * b.min1);
			if (b.max2 != inf) cmin(ans3, 1ll * a.min1 * b.max2);
		}
		if (a.min2 != -inf) {
			if (b.max1 != -inf) cmin(ans4, 1ll * a.min2 * b.max1);
			if (b.min2 != -inf) cmin(ans4, 1ll * a.min2 * b.min2);
		}

		if (ans1 == INF) ans1 = -ans1; if (ans2 == INF) ans2 = -ans2;
		if (ans3 == INF) ans3 = -ans3; if (ans4 == INF) ans4 = -ans4;

		printf("%lld\n", std::max({ans1, ans2, ans3, ans4}));
	}
	return 0;
}