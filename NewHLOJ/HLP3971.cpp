#include <bits/stdc++.h>

#define range(l, r) Range<int>(l, r + 1)
#define ep emplace
#define eb emplace_back

template<typename T>
class Iterator {
	public:
		Iterator(T _val = 0): _value(_val) {}
		bool operator != (const Iterator &other) const {
			return this -> _value != other._value;
		}
		const T & operator *() {return _value;}
		T operator ++() {return ++ _value;}
	private:
		T _value;
};
template<typename T>
class Range {
	public:
		Range(T l = 0, T r = 0): __begin(l), __end(r) {}
		Iterator<T> begin() {return Iterator<T>(__begin);}
		Iterator<T> end() {return Iterator<T>(__end);}
	private:
		T __begin;
		T __end;
};

static constexpr int N = 1e5 + 5, inf = 1e9 + 7, P = inf;

int inc(auto x, auto y) {return (x + y) % P;}
int dec(auto x, auto y) {return (x + P - y) % P;}
int mul(auto x, auto y) {return 1LL * x * y % P;} 

int n, q, a[N], b[N], ans[N], last1[N], last2[N];
class issue {
	public:
		int l, id;
		issue(int l = 0, int id = 0): l(l), id(id) {}
};
std::vector<issue> qu[N];
class TreeNode {
	public:
		int sum, xy, x, y;
		TreeNode(int sum = 0, int xy = 0, int x = 0, int y = 0):
			sum(sum), xy(xy), x(x), y(y) {}
} tr[N << 2];
class tag {
	public:
		int cx, cy, xy, x, y, c;
		tag(int cx = 0, int cy = 0, int xy = 0, int x = 0, int y = 0, int c = 0):
			cx(cx), cy(cy), xy(xy), x(x), y(y), c(c) {}
		bool val();
} lazy[N << 2];
inline bool tag::val() {return cx | cy | xy | x | y | c;}

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

void seg_up(int x) {
	tr[x].sum = inc(tr[ls(x)].sum, tr[rs(x)].sum);
	tr[x].xy = inc(tr[ls(x)].xy, tr[rs(x)].xy);
	tr[x].x = inc(tr[ls(x)].x, tr[rs(x)].x);
	tr[x].y = inc(tr[ls(x)].y, tr[rs(x)].y);
}

void seg_push(int x, int l, int r, tag t) {
	{
		auto &[cx, cy, xy, sx, sy, c] = lazy[x];
		if (cx && cy) c = inc(c, inc(inc(inc(mul(t.xy, mul(cx, cy)), mul(t.x, cx)), mul(t.y, cy)), t.c));
		else if (cx) c = inc(c, inc(mul(t.x, cx), t.c)), sy = inc(sy, inc(mul(t.xy, cx), t.y));
		else if (cy) c = inc(c, inc(mul(t.y, cy), t.c)), sx = inc(sx, inc(mul(t.xy, cy), t.x));
		else xy = inc(xy, t.xy), sx = inc(sx, t.x), sy = inc(sy, t.y), c = inc(c, t.c);
		if (t.cx) cx = t.cx;
		if (t.cy) cy = t.cy;
	}

	{
		#define len (r - l + 1)
		auto &[sum, xy, sx, sy] = tr[x];
		sum = inc(sum, inc(mul(t.xy, xy), inc(mul(t.x, sx), inc(mul(t.y, sy), mul(t.c, len)))));
		if (t.cx && t.cy) xy = mul(mul(t.cx, t.cy), len), sx = mul(t.cx, len), sy = mul(t.cy, len);
		else if (t.cx) xy = mul(t.cx, sy), sx = mul(t.cx, len);
		else if (t.cy) xy = mul(t.cy, sx), sy = mul(t.cy, len);
		#undef len
	}
}

void seg_down(int x, int l, int r) {
	#define mid ((l + r) >> 1)
	if (lazy[x].val()) {
		seg_push(ls(x), l, mid, lazy[x]);
		seg_push(rs(x), mid + 1, r, lazy[x]);
		lazy[x] = tag();
	}
	return void();
	#undef mid
}

void seg_upd(int x, int l, int r, int ql, int qr, tag t) {
	#define mid ((l + r) >> 1)
	if (ql <= l && r <= qr) return seg_push(x, l, r, t);
	seg_down(x, l, r);
	if (ql <= mid) seg_upd(ls(x), l, mid, ql, qr, t);
	if (qr > mid) seg_upd(rs(x), mid + 1, r, ql, qr, t);
	return seg_up(x);
	#undef mid
}

int seg_qry(int x, int l, int r, int ql, int qr) {
	#define mid ((l + r) >> 1)
	if (ql <= l && r <= qr) return tr[x].sum;
	seg_down(x, l, r); int ans = 0;
	if (ql <= mid) ans = inc(ans, seg_qry(ls(x), l, mid, ql, qr));
	if (qr > mid) ans = inc(ans, seg_qry(rs(x), mid + 1, r, ql, qr));
	return ans;
	#undef mid
}

signed main() {
    scanf("%d%d", &n, &q); a[0] = b[0] = inf;
	
	for (auto i : range(1, n)) {
		scanf("%d", a + i);
		last1[i] = i;
		while (a[i] > a[last1[i] - 1]) last1[i] = last1[last1[i] - 1];
	}
	for (auto i : range(1, n)) {
		b[i] = a[i];
		last2[i] = i;
		while (b[i] < b[last2[i] - 1]) last2[i] = last2[last2[i] - 1];
	}
	
	for (auto i : range(1, q)) {
		static int l, r;
		scanf("%d%d", &l, &r);
		qu[r].eb(l, i);
	}
	for (auto r : range(1, n)) {
		seg_upd(1, 1, n, last1[r], r, tag(a[r], 0, 0, 0, 0, 0));
		seg_upd(1, 1, n, last2[r], r, tag(0, b[r], 0, 0, 0, 0));
		seg_upd(1, 1, n, 1       , r, tag(0, 0, 1, 0, 0, 0));
		for (auto [l, id] : qu[r]) ans[id] = seg_qry(1, 1, n, l, r);
	}
	for (auto i : range(1, q)) printf("%d\n", ans[i]);
    return 0;
}