#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5, P = 1e4;
int n, m, k, ans, a[N], Pow[N], next[N];
void Init(int m) {
	for (int i = 2, j = 0; i <= m; ++i) {
		while (j && a[i] != a[j + 1]) j = next[j];
		if (a[i] == a[j + 1]) next[i] = j + 1, ++ j;
	}
}
signed main() {
	scanf("%d%d", &n, &k); n %= P;
	for (int i = Pow[0] = 1; i < N; ++i) Pow[i] = Pow[i - 1] * n % P;
	for (int i = 1; i <= k; ++i) {
		scanf("%d", &m); ans = 0;
		for (int j = 1; j <= m; ++j) scanf("%d", a + j), next[j] = 0;
		Init(m);
		for (int j = m; j; j = next[j]) ans = (ans + Pow[j]) % P;
		printf("%04d\n", ans); 
	} return 0;
}