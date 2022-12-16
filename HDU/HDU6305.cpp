#include <bits/stdc++.h>
static constexpr int N = 1e6 + 5, P = 1e9 + 7;
int n, top, ans, root;
int a[N], ls[N], rs[N], st[N], inv[N], size[N];
void dfs(int x) {
    size[x] = 1;
    if (ls[x]) dfs(ls[x]), size[x] += size[ls[x]];
    if (rs[x]) dfs(rs[x]), size[x] += size[rs[x]];
    ans = 1ll * ans * inv[size[x]] % P;
}
void solve() {
    scanf("%d", &n); 
    ans = 1ll * n * inv[2] % P;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) ls[i] = rs[i] = 0;
    for (int i = 1; i <= n; ++i) {
        while (top && a[st[top]] > a[i]) ls[i] = st[top --];
        if (st[top]) rs[st[top]] = i;
        st[++ top] = i;
    }
    while (top) root = st[top --];
    dfs(root);
    printf("%d\n", ans);
}
signed main() {
    inv[1] = 1;
    for (int i = 2; i < N; ++i) inv[i] = 1ll * inv[P % i] * (P - P / i) % P;
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}