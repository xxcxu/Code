#include <bits/stdc++.h>

template<typename T>
void read(T &x) {
	x = 0; bool f = false; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}

#define range Range<int>
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

static constexpr int N = 3e5 + 5;
int n, k;
int a[N], b[N], st[N], ans[N];

void solve() {
	read(n, k);
	for (auto i : range(1, n)) read(a[i]);
	int top = 0, tot = 0;
	for (auto i : range(1, n)) {
		if (tot >= k) {st[++ top] = a[i]; continue;}
		while (top && tot < k && st[top] < a[i]) b[++ tot] = st[top --];
		st[++ top] = a[i];
	}
	std::sort(b + 1, b + tot + 1, [&](int x, int y) {return x > y;});
	int cnt = 0, i = 1, j = 1;
	for (; i <= tot && j <= top;) {
		if (b[i] > st[j]) ans[++ cnt] = b[i ++];
		else ans[++ cnt] = st[j ++];
	}
	while (i <= tot) ans[++ cnt] = b[i ++];
	while (j <= top) ans[++ cnt] = st[j ++];
	for (auto i : range(1, n)) printf("%d%c", ans[i], " \n"[i == n]);
}

signed main() {
	int t; read(t);
	while (t--) solve();
	return 0;
}