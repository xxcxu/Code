#include <bits/stdc++.h>

#define ep emplace
#define range(l, r) Range<int>(l, r)

using PII = std::pair<int, int>;
using LL = long long;

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
		Range(T l = 0, T r = 0): __begin(l), __end(r + 1) {}
		Iterator<T> begin() {return Iterator<T>(__begin);}
		Iterator<T> end() {return Iterator<T>(__end);}
	private:
		T __begin;
		T __end;
};

static constexpr int N = 25e4 + 5, P = 1e9 + 7;

int n, a[N];

int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}

int solve(int L, int R) {
	static int t[N], ma[N], mb[N], sa[N], sb[N];
	#define mid ((L + R) >> 1)
	if (L == R) return mul(a[L], a[L]);
	if (L == R - 1) return inc(inc(mul(a[L], a[L]), mul(a[R], a[R])), mul(std::max(a[L], a[R]), std::min(a[L], a[R])));
	int ans = inc(solve(L, mid - 1), solve(mid + 1, R));
	ma[mid] = sa[mid] = a[mid], mb[mid] = sb[mid] = a[mid], t[mid] = mul(a[mid], a[mid]);
	for (auto i : range(mid + 1, R)) ma[i] = std::max(ma[i - 1], a[i]), mb[i] = std::min(mb[i - 1], a[i]);
	for (auto i = mid - 1; i >= L; --i) ma[i] = std::max(ma[i + 1], a[i]), mb[i] = std::min(mb[i + 1], a[i]);
	for (auto i = mid - 1; i >= L; --i) t[i] = inc(t[i + 1], mul(ma[i], mb[i]));
	for (auto i = mid - 1; i >= L; --i) sa[i] = inc(sa[i + 1], ma[i]), sb[i] = inc(sb[i + 1], mb[i]);
	int j, k; j = k = mid;
	for (auto i : range(mid, R)) {
		while (j > L && ma[j - 1] <= ma[i]) -- j;
		while (k > L && mb[k - 1] >= mb[i]) -- k;
		if (j > k) {
			ans = inc(ans, mul(mid - j + 1, mul(ma[i], mb[i])));
			ans = inc(ans, mul(mb[i], dec(sa[k], sa[j])));
			ans = inc(ans, dec(t[L], t[k]));
		} else {
			ans = inc(ans, mul(mid - k + 1, mul(ma[i], mb[i])));
			ans = inc(ans, mul(ma[i], dec(sb[j], sb[k])));
			ans = inc(ans, dec(t[L], t[j]));
		}
	}
	return ans;	
	#undef mid
}

signed main() { 
    scanf("%d", &n);
    for (auto i : range(1, n)) scanf("%d", a + i);
	printf("%d\n", solve(1, n));
    return 0;	
}
