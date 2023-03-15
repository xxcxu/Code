#include <bits/stdc++.h>

#define int long long
#define fi first
#define se second
#define eb emplace_back
#define all(x) x.begin(), x.end()
using PII = std::pair<int, int>;

FILE *fin, *fout, *ferr;
static const int N = 200'005;

int n, m, t;
struct Node
{
	int fi, se, id;
	Node(int fi = 0, int se = 0, int id = 0) : fi(fi), se(se), id(id) {}
	bool operator<(const Node &a) { return std::tie(fi, se) < std::tie(a.fi, a.se); }
} a[N];
int b[N], cnt[N];
std::vector<int> vec[N];
std::vector<PII> c, d;

struct SegmentTree
{
	int sum[N << 2], num[N << 2];
#define ls (x << 1)
#define rs (x << 1 | 1)
	void pushup(int x)
	{
		sum[x] = sum[ls] + sum[rs];
		num[x] = num[ls] + num[rs];
		return void();
	}
	void build(int x, int l, int r, int op)
	{
		if (l == r)
		{
			sum[x] = b[l] * cnt[l] * op;
			num[x] = cnt[l] * op;
			return void();
		}
		int mid = (l + r) >> 1;
		build(ls, l, mid, op);
		build(rs, mid + 1, r, op);
		return pushup(x);
	}
	void add(int x, int l, int r, int p, int v)
	{
		if (l == r)
		{
			sum[x] += v * b[l];
			num[x] += v;
			return void();
		}
		int mid = (l + r) >> 1;
		p <= mid ? (add(ls, l, mid, p, v), 0) : (add(rs, mid + 1, r, p, v), 0);
		return pushup(x);
	}
	int ask(int x, int l, int r, int v)
	{
		if (!v)
			return 0;
		if (num[x] == v)
			return sum[x];
		if (l == r)
			return v * b[l];
		int mid = (l + r) >> 1;
		if (v <= num[ls])
			return ask(ls, l, mid, v);
		else
			return sum[ls] + ask(rs, mid + 1, r, v - num[ls]);
	}
} t1, t2;

void discrete()
{
	for (int i = 1; i <= n; ++i)
		b[i] = a[i].fi;
	std::sort(b + 1, b + n + 1);
	m = std::unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; ++i)
		a[i].fi = std::lower_bound(b + 1, b + m + 1, a[i].fi) - b;
	for (int i = 1; i <= n; ++i)
		++cnt[a[i].fi];
	return void();
}

void solve()
{
	m = 0;
	c.clear(), d.clear();
	fscanf(fin, "%lld%lld", &n, &t);
	for (int i = 1; i <= n; ++i)
		cnt[i] = 0;
	for (int i = 1; i <= n; ++i)
		vec[i].clear();
	for (int i = 1; i <= n; ++i)
		fscanf(fin, "%lld%lld", &a[i].fi, &a[i].se), a[i].id = i;
	discrete();
	for (int i = 1; i <= n; ++i)
		vec[a[i].se].eb(a[i].fi);
	t1.build(1, 1, n, 0);
	t2.build(1, 1, n, 1);
	int ans = 0, p = 0, sum = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j : vec[i])
		{
			t1.add(1, 1, n, j, 1);
			t2.add(1, 1, n, j, -1);
			++sum;
		}
		int l = std::max(ans + 1, i - (n - sum));
		int r = std::min(sum, i);
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (t1.ask(1, 1, n, mid) + t2.ask(1, 1, n, i - mid) <= t)
				l = mid + 1, ans = mid, p = i;
			else
				r = mid - 1;
		}
	}
	fprintf(fout, "%lld\n%lld\n", ans, p);
	for (int i = 1; i <= n; ++i)
		if (a[i].se <= p)
			c.eb(a[i].fi, i);
		else
			d.eb(a[i].fi, i);
	std::sort(all(c)), std::sort(all(d));
	for (int i = 0; i < ans; ++i)
		fprintf(fout, "%lld ", c[i].se);
	for (int i = 0; i < p - ans; ++i)
		fprintf(fout, "%lld ", d[i].se);
	fputs("\n", fout);
	return void();
}

signed main()
{
	fin = fopen("easy.in", "r");
	fout = fopen("easy.out", "w+");
	ferr = stderr;
	// fin = fopen("Input.txt", "r");
	// fout = fopen("Output.txt", "w+");
	// ferr = stderr;
	int t;
	fscanf(fin, "%lld", &t);
	while (t--)
		solve();
	return 0;
}