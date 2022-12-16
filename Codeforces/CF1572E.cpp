#include<bits/stdc++.h>
#define int long long
const int N = 4e4 + 5;
int n, m, ans, x, L = 1, R;
int a[N], prev[N], next[N], last[N], f[101][N];
void DelL(int x) {if (next[x] <= R) ans -= next[x] - x;}
void AddL(int x) {if (next[x] <= R) ans += next[x] - x;}
void DelR(int x) {if (prev[x] >= L) ans -= x - prev[x];}
void AddR(int x) {if (prev[x] >= L) ans += x - prev[x];}
void Update(int l, int r) {
	while(L < l) DelL(L ++); 
	while(R > r) DelR(R --);
	while(L > l) AddL(-- L);
	while(R < r) AddR(++ R);
}
void Solve(int l, int r, int ql, int qr) {
	if (l > r) return void();
	int pos = 0, mid = l + r >> 1;
	for (int i = ql; i <= std::min(qr, mid - 1); ++i) {
		Update(i + 1, mid);
		if (f[x - 1][i] + ans < f[x][mid]) 
			f[x][mid] = f[x - 1][i] + ans, pos = i;
	} Solve(l, mid - 1, ql, pos); Solve(mid + 1, r, pos, qr);
}
signed main() {
	std::memset(f, 0x3f, sizeof f);
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
	for (int i = 1; i <= n; ++i) last[i] = 0;
	for (int i = 1; i <= n; ++i) prev[i] = last[a[i]], last[a[i]] = i;
	for (int i = 1; i <= n; ++i) last[i] = n + 1;
	for (int i = n; i >= 1; --i) next[i] = last[a[i]], last[a[i]] = i;
	for (int i = 1; i <= n; ++i) Update(1, i), f[1][i] = ans;
	for (int i = 2; i <= m; ++i) x = i, Solve(1, n, 0, n - 1);
	return printf("%lld", f[m][n]), 0;
}
