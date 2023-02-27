# include <bits/stdc++.h>

using pii = std::pair<int, int>;
using LL = long long;

# define gc getchar
# define eb emplace_back
# define ep emplace

int read() {
	int x = 0, f = 0; char ch = gc();
	for (; !isdigit(ch); ch = gc()) f ^= (ch == '-');
	for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
	return f ? -x : x;
}

static const int N = 100005;

int n, k, flag;
int a[N], b[N], c[N];

bool equal(int l, int r, int *a) {
	for (int i = l; i <= r; ++i)
		if (a[i] != i) return false;
	return true;
}
bool equal2(int l, int r, int *b) {
	for (int i = l; i <= r; ++i)
		if (b[i] != a[i]) return false;
	return true;
}
void solve0() {if (equal(1, n, a)) {puts("TAK"); exit(0);}}
void solve1() {
	std::vector<int> p;
	for (int i = 1; i <= n; ++i) if (a[i] != i) p.eb(i);
	if (p.empty()) {
		puts("TAK");
		printf("%d %d\n", 1, 1);
		exit(0);
	}
	int l = *p.begin(), r = *std::prev(p.end());
	std::reverse(a + l, a + r + 1);
	if (equal(l, r, a)) {
		puts("TAK");
		printf("%d %d\n", l, r);
		exit(0);
	}
}
void solve2(int l0, int r0, int l1, int r1) {
	static int l[2], r[2], p[2];
	l[0] = l0, l[1] = l1;
	r[0] = r0, r[1] = r1;
	std::iota(p, p + 2, 0);
	do {
		for (int i = 1; i <= n; ++i) b[i] = a[i];
		for (int i = 0; i <= 1; ++i) std::reverse(b + l[p[i]], b + r[p[i]] + 1);
		if (equal(1, n, b)) {
			puts("TAK");
			for (int i = 0; i <= 1; ++i) printf("%d %d\n", l[p[i]], r[p[i]]);
			exit(0);
		}
	} while (std::next_permutation(p, p + 2));
}
void solve3(int l0, int r0, int l1, int r1, int l2, int r2) {
	static int l[3], r[3], p[3];
	l[0] = l0, l[1] = l1, l[2] = l2;
	r[0] = r0, r[1] = r1, r[2] = r2;
	std::iota(p, p + 3, 0);
	do {
		for (int i = 1; i <= n; ++i) b[i] = a[i];
		for (int i = 0; i <= 2; ++i) std::reverse(b + l[p[i]], b + r[p[i]] + 1);
		if (equal(1, n, b)) {
			puts("TAK");
			for (int i = 0; i <= 2; ++i) printf("%d %d\n", l[p[i]], r[p[i]]);
			exit(0);
		}
	} while (std::next_permutation(p, p + 3));
}
namespace brute_force {
	void brute() {
		if (k == 2) {
			for (int l0 = 1; l0 <= n; ++l0)
				for (int r0 = l0; r0 <= n; ++r0)
					for (int l1 = l0; l1 <= n; ++l1)
						for (int r1 = l1; r1 <= n; ++r1)
							solve2(l0, r0, l1, r1);
		}
		if (k == 3) {
			for (int l0 = 1; l0 <= n; ++l0)
				for (int r0 = l0; r0 <= n; ++r0)
					for (int l1 = l0; l1 <= n; ++l1)
						for (int r1 = l1; r1 <= n; ++r1)
							for (int l2 = l1; l2 <= n; ++l2)
								for (int r2 = l2; r2 <= n; ++r2)
									solve3(l0, r0, l1, r1, l2, r2);
		}
	}
};
using namespace brute_force;
int check(std::vector<int> &v) {
	int cnt = 0;
	for (int i = 2; i <= n; ++i)
		if (a[i] != a[i - 1] + 1) ++ cnt;
	return cnt;
}
void solve2() {
	auto bes = [&](int l0, int r0) -> void {
		std::reverse(a + l0, a + r0 + 1);
		std::vector<int> p2;
		for (int i = 1; i <= n; ++i) if (a[i] != i) p2.eb(i);
		if (p2.empty()) {
			puts("TAK");
			printf("%d %d\n", l0, r0);
			printf("%d %d\n", 1, 1);
			exit(0);
		}
		int l1 = *p2.begin(), r1 = *std::prev(p2.end());
		std::reverse(a + l1, a + r1 + 1);
		if (equal(1, n, a)) {
			puts("TAK");
			printf("%d %d\n", l0, r0);
			printf("%d %d\n", l1, r1);
			exit(0);
		}
		std::reverse(a + l1, a + r1 + 1);
		std::reverse(a + l0, a + r0 + 1);
	};
	auto cov = [&](int l0, int r0) -> void {
		bes(l0, r0);
		std::iota(b + 1, b + n + 1, 1);
		std::reverse(b + l0, b + r0 + 1);
		std::vector<int> p2;
		for (int i = 1; i <= n; ++i) if (b[i] != a[i]) p2.eb(i);
		if (p2.empty()) {
			puts("TAK");
			printf("%d %d\n", 1, 1);
			printf("%d %d\n", l0, r0);
			exit(0);
		}
		int l1 = *p2.begin(), r1 = *std::prev(p2.end());
		std::reverse(b + l1, b + r1 + 1);
		if (equal2(1, n, b)) {
			puts("TAK");
			printf("%d %d\n", l1, r1);
			printf("%d %d\n", l0, r0);
			exit(0);
		}
	};
	std::vector<int> p;
	for (int i = 1; i <= n; ++i) if (a[i] != i) p.eb(i);
	for (int i = 1; i <= n; ++i) c[a[i]] = i;
	if (p.empty()) {
		puts("TAK");
		printf("%d %d\n", 1, 1);
		printf("%d %d\n", 1, 1);
		exit(0);
	}
	int l0 = *p.begin();
	if (check(p) == 1) bes(l0, a[l0]);
	else {
		cov(l0, a[l0]);
		cov(l0, c[l0]);
	}
	return void();
}
void solve3() {
	puts("NIE");
}

signed main() {
	freopen("rev.in", "r", stdin);
	freopen("rev.out", "w", stdout);
	n = read(), k = read();
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    if (k == 0) solve0();
	else if (k == 1) solve1();
	else if (k == 2) solve2();
	else if (n <= 16) brute();
	puts("NIE");
} // :) 精神状态良好