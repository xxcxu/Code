#include <bits/stdc++.h>

#define range(l, r) Range<int>(l, r + 1)
#define ep emplace
#define eb emplace_back
using uLL = unsigned long long;

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

static constexpr int N = 25e4 + 5, inf = 1e9 + 7;

int n, q, last1[N], last2[N];
uLL a[N], b[N], ans[N];
class issue {
	public:
		int l, id;
		issue(int l = 0, int id = 0): l(l), id(id) {}
};
std::vector<issue> qu[N];
class TreeNode {
	public:
		uLL sum, xy, x, y;
		TreeNode(uLL sum = 0, uLL xy = 0, uLL x = 0, uLL y = 0):
			sum(sum), xy(xy), x(x), y(y) {}
} tr[N << 2];
class tag {
	public:
		uLL cx, cy, xy, x, y, c;
		tag(uLL cx = 0, uLL cy = 0, uLL xy = 0, uLL x = 0, uLL y = 0, uLL c = 0):
			cx(cx), cy(cy), xy(xy), x(x), y(y), c(c) {}
		bool val();
} lazy[N << 2];
inline bool tag::val() {return cx | cy | xy | x | y | c;}

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

void seg_up(int x) {
	tr[x].sum = tr[ls(x)].sum + tr[rs(x)].sum;
	tr[x].xy = tr[ls(x)].xy + tr[rs(x)].xy;
	tr[x].x = tr[ls(x)].x + tr[rs(x)].x;
	tr[x].y = tr[ls(x)].y + tr[rs(x)].y;
}

void seg_push(int x, int l, int r, tag t) {
	{
		auto &[cx, cy, xy, sx, sy, c] = lazy[x];
		if (cx && cy) c += t.xy * cx * cy + t.x * cx + t.y * cy + t.c;
		else if (cx) c += t.x * cx + t.c, sy += t.xy * cx + t.y;
		else if (cy) c += t.y * cy + t.c, sx += t.xy * cy + t.x;
		else xy += t.xy, sx += t.x, sy += t.y, c += t.c;
		if (t.cx) cx = t.cx;
		if (t.cy) cy = t.cy;
	}

	{
		#define len (r - l + 1)
		auto &[sum, xy, sx, sy] = tr[x];
		sum += t.xy * xy + t.x * sx + t.y * sy + t.c * len;
		if (t.cx && t.cy) xy = t.cx * t.cy * len, sx = t.cx * len, sy = t.cy * len;
		else if (t.cx) xy = t.cx * sy, sx = t.cx * len;
		else if (t.cy) xy = t.cy * sx, sy = t.cy * len;
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

uLL seg_qry(int x, int l, int r, int ql, int qr) {
	#define mid ((l + r) >> 1)
	if (ql <= l && r <= qr) return tr[x].sum;
	seg_down(x, l, r); uLL ans = 0;
	if (ql <= mid) ans += seg_qry(ls(x), l, mid, ql, qr);
	if (qr > mid) ans += seg_qry(rs(x), mid + 1, r, ql, qr);
	return ans;
	#undef mid
}

signed main() {
    scanf("%*d%d", &n); a[0] = b[0] = inf;
	
	for (auto i : range(1, n)) {
		scanf("%llu", a + i);
		last1[i] = i;
		while (a[i] > a[last1[i] - 1]) last1[i] = last1[last1[i] - 1];
	}
	for (auto i : range(1, n)) {
		scanf("%llu", b + i);
		last2[i] = i;
		while (b[i] > b[last2[i] - 1]) last2[i] = last2[last2[i] - 1];
	}
	
	scanf("%d", &q);
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
	for (auto i : range(1, q)) printf("%llu\n", ans[i]);
    return 0;
}