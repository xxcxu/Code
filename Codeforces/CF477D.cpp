#include <bits/stdc++.h>
static constexpr int N = 5e3 + 5, inf = 0x3f3f3f3f, P = 1e9 + 7;
int n, ans = inf;
int lcp[N][N], f[N][N], sum[N][N], pre[N][N];
char s[N];
bool check(int l1, int r1, int l2, int r2) {
	int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
	if (len1 != len2) return len1 < len2;
	if (l1 + lcp[l1][l2] > r1)return 1;
	return s[l1 + lcp[l1][l2]] < s[l2 + lcp[l1][l2]];
}
auto main() -> decltype(0) {
	std::memset(pre, 0x3f, sizeof pre);
	std::memset(f, 0x3f, sizeof f);
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for (int i = n; i; --i)
		for (int j = n; j; --j)
			if (s[i] == s[j])
				lcp[i][j] = lcp[i + 1][j + 1] + 1;
			else
				lcp[i][j] = 0;
	for (int r = 1; r <= n; ++r) {
		for (int l = r, k = l - 1; l; --l) {
			int t = 0;
			if (l == 1) f[l][r] = t = 1;
			else {
				while (k > 1 && check(k - 1, l - 1, l, r)) -- k;
				if (s[l] == '1')
					t = sum[k][l - 1], f[l][r] = std::min(pre[k][l - 1] + 1, inf);
			}
			sum[l][r] = (sum[l + 1][r] + t) % P;
			pre[l][r] = std::min(pre[l + 1][r], f[l][r]);
		}
	}
	int t = 1, cur = 0;
	for (int i = n; i; t = (t << 1) % P, --i) {
		cur = (cur + t * (s[i] - '0') % P) % P;
		if (f[i][n] < inf) {
			if (n - i < 27) ans = std::min(ans, (cur + f[i][n]) % P);
			else {
				if (ans == inf) ans = (cur + f[i][n]) % P;
				break;
			}
		}
	}
	printf("%d\n%d\n", sum[1][n], ans);
	return 0;
}