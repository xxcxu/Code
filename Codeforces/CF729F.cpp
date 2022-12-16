#include <bits/stdc++.h>
static constexpr int N = 4e3 + 5, P = 3e7 - 1, inf = 1e9 + 7;
int n, a[N], sum[N], f[P + 5];
auto Ask(int l, int r) -> int {
    return sum[r] - sum[l - 1];
}
auto Hash(int i, int j, int k, int l) -> int {
    return ((((1ll * i * 4000 + j) * 100) + k) * 2 + l) % P;
}
auto Dfs(int l, int r, int last, int k) -> int {
    if (r - l + 1 < last) return 0;
    if (r - l + 1 == last) return Ask(l, r) * (k ? -1 : 1);
    int mask = Hash(l, r, last, k);
    if (f[mask] != -1) return f[mask];
	int ans;
    if (k) { // Bob
		ans = Dfs(l, r - last, last, k ^ 1) - Ask(r - last + 1, r);
		if (r - last >= l)
			ans = std::min(ans, Dfs(l, r - last - 1, last + 1, k ^ 1) - Ask(r - last, r));	
    } else { // Alice
		ans = Dfs(l + last, r, last, k ^ 1) + Ask(l, l + last - 1);
		if (l + last <= r)
			ans = std::max(ans, Dfs(l + last + 1, r, last + 1, k ^ 1) + Ask(l, l + last)); 
    }
	return f[mask] = ans;
}
auto main() -> decltype(0) {
	scanf("%d", &n);
	std::memset(f, -1, sizeof f);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
	return printf("%d\n", Dfs(1, n, 1, 0)), 0;
}