#include <bits/stdc++.h>
const int N = 200005;
int n, ans;
int a[N], b[N], c[N], d[N];
std::set<int> set, s[N];
signed main() {
    freopen("farm.in", "r", stdin);
    freopen("farm.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", a + i, b + i);
	for (int i = 1; i <= n; ++i) scanf("%d%d", c + i, d + i);
	std::reverse(a + 1, a + n + 1);
	std::reverse(b + 1, b + n + 1);.
	std::reverse(c + 1, c + n + 1);
	std::reverse(d + 1, d + n + 1);
	for (int i = 1; i <= n; ++i) s[a[i]].insert(i);
	for (int i = 1; i <= n; ++i) set.insert(i);
	for (int i = 1; i <= n; ++i) {
		int p = std::upper_bound(b + 1, b + n + 1, d[i]) - b - 1;
		if (s[c[i]].size() && s[c[i]].upper_bound(p) != s[c[i]].begin()) {
			auto it = std::prev(s[c[i]].upper_bound(p));
			if (set.upper_bound(*it) != set.begin()) set.erase(std::prev(set.upper_bound(*it))), s[c[i]].erase(it);
			else set.erase(std::prev(set.upper_bound(p))), ++ ans;
		} 
		else set.erase(std::prev(set.upper_bound(p))), ++ ans;
	}
	return printf("%d\n", ans), 0;
}