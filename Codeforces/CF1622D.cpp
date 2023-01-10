#include <bits/stdc++.h>
static const int N = 5005, P = 998244353;
int n, k, ans, sum, a[N], c[N][N];
char s[N];
int inc(int x, int y) {return (x + y) % P;}
signed main() {
	scanf("%d%d%s", &n, &k, s + 1); ans = 1;
	for (int i = 1; i <= n; ++i) a[i] = s[i] - '0';
	for (int i = 1; i <= n; ++i) sum += a[i];
	if (sum < k) return puts("1"), 0;
	c[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		c[i][0] = 1;
		for (int j = 1; j <= i; ++j) c[i][j] = inc(c[i - 1][j], c[i - 1][j - 1]);
	}
	for (int i = 1; i <= n; ++i) {
		int cnt = a[i];
		int c0 = 0, c1 = 0;
		c0 += (a[i] == 1 ? -1 : 1);
		c1 += (a[i] == 1 ? 1 : -1);
		for (int j = i + 1; j <= n; ++j) {
			c0 += a[j] == 0, c1 += a[j] == 1;
			cnt += a[j];
			if (cnt > k) break;
			int cc0 = c0, cc1 = c1;
			(a[j] ? cc0 : cc1) -= 1;
			if (cc0 >= 0 && cc1 >= 0) ans = inc(ans, c[cc0 + cc1][cc0]);
		}
	}
	printf("%d\n", ans);
	return 0;
}