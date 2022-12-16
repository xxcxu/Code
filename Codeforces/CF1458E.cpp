#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e5 + 5;
int n, m, x, top, ans, a[N], b[N], s[N], st[N], max[N];
int prea[N], sufa[N], preb[N], sufb[N], na[N], nb[N];
std::vector<int> qa[N], qb[N];
auto add(int x, int v) -> void {for (; x < N; x += x & -x) s[x] += v;}
auto ask(int x) -> int {int ans = 0; for (; x; x -= x & -x) ans += s[x]; return ans;}
auto Calc(int nn, int *a, int *b, int type) -> void {
	top = 1;
	for (int i = type ? nn : 1; type ? i : i <= nn; type ? --i : ++i) {
		while (a[i] - type < a[st[top - 1]]) {
			max[top - 2] = std::max(max[top - 2], max[top - 1]);
			-- top;
		}
		b[i] = std::max(max[top - 1], a[i]);
		st[top] = i, max[top ++] = a[i];
	}
}
auto main() -> decltype(0) {
	scanf("%lld%lld%lld", &n, &m, &x);
	for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
	for (int i = 1; i <= m; ++i) scanf("%lld", b + i);
	max[0] = N - 1, Calc(n, a, prea, 0), Calc(m, b, preb, 0);
	st[0] = n + 1, Calc(n, a, sufa, 1);
	st[0] = m + 1, Calc(m, b, sufb, 1);
	for (int i = 1; i <= n; ++i) na[i] = std::min(prea[i], sufa[i]);
	for (int i = 1; i <= m; ++i) nb[i] = std::min(preb[i], sufb[i]);
	for (int i = 1; i <= n; ++i) if (a[i] <= x) qa[x - a[i]].push_back(i);
	for (int i = 1; i <= m; ++i) qb[nb[i]].push_back(i);
	for (int i = N - 1; i; --i) {
		for (int j : qa[i]) ans += ask(x - a[j]) - ask(std::max(x - na[j], 0ll));
		for (int j : qb[i]) add(b[j], 1);
	} return printf("%lld\n", ans), 0;
}