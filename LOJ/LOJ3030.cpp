#include <bits/stdc++.h>
static constexpr int N = 2e5 + 5;
struct Node {int a, b, c, id;} f[N], g[N];
int n, m, q, ans[N], s[N], c[N];
void Add(int x, int v) {for (; x; x -= x & -x) s[x] += v;}
int Ask(int x) {int ans = 0; for (; x <= m; x += x & -x) ans += s[x]; return ans;}
void Cdq(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	Cdq(l, mid); Cdq(mid + 1, r);
	int j = l, k = l - 1;
	for (int i = mid + 1; i <= r; ++i) {
		while (j <= mid && f[j].b >= f[i].b) {
			if (!f[j].id) Add(f[j].c, 1);
			g[++ k] = f[j ++];
		}
		if (f[i].id) ans[f[i].id] += Ask(f[i].c);
		g[++ k] = f[i];
	}
	for (int i = l; i < j; ++i) if (!f[i].id) Add(f[i].c, -1);
	for (int i = j; i <= mid; ++i) g[++ k] = f[i];
	for (int i = l; i <= r; ++i) f[i] = g[i];
}
bool Compare(Node a, Node b) {
	if (a.a != b.a) return a.a > b.a;
	if (a.b != b.b) return a.b > b.b;
	if (a.c != b.c) return a.c > b.c;
	return a.id < b.id;
}
signed main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", &f[i].a, &f[i].b), f[i].c = f[i].a + f[i].b;
	for (int i = 1; i <= q; ++i)
		scanf("%d%d%d", &f[n + i].a, &f[n + i].b, &f[n + i].c), f[n + i].id = i;
	n = n + q;
	for (int i = 1; i <= n; ++i) c[i] = f[i].c;
	std::stable_sort(c + 1, c + n + 1);
	m = std::unique(c + 1, c + n + 1) - c - 1;
	for (int i = 1; i <= n; ++i)
		f[i].c = std::lower_bound(c + 1, c + m + 1, f[i].c) - c;
	std::stable_sort(f + 1, f + n + 1, Compare);
	Cdq(1, n);
	for (int i = 1; i <= q; ++i) ntf("%d\n", ans[i]);
	return 0;
}