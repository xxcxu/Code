#include <bits/stdc++.h>
static constexpr int N = 1e6 + 5, M = 5e6 + 5;
int n, m, ans, a[N], b[M], cnt[M], dp[M];
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) dp[i] = i;
	for (int i = 1; i <= m; ++i) b[i] = cnt[i] = 0;
	int min = 1e9, max = -1e9;
	for (int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		min = std::min(min, x);
		max = std::max(max, x);
		b[x] = cnt[x] = 1;
	}
	ans = max - min;
	for (int i = (int)std::sqrt(m) + 1; i >= 1; --i) {
		for (int j = i; j <= m; j += i) {
			if (b[j]) -- cnt[dp[j]];
			if (dp[j / i] >= i) dp[j] = std::min(dp[j], dp[j / i]);
			if (b[j]) ++ cnt[dp[j]];
		}
		while (!cnt[max]) -- max;
		ans = std::min(ans, max - std::min(i, min));
	} printf("%d\n", ans);
}
int main() {
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}

