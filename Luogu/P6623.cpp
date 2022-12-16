#include <bits/stdc++.h>
using ud = unsigned; using ull = ud long long;
const int N = 21, S = 1 << N;
int n; ull ans; ud a[S], w[N][S];
std::vector<int> Graph[S];
ud Dfs(int x, ud dep) {
    ud ans2 = a[x];
    for (int i = 0; i < N; ++i) w[i][(dep + a[x]) & ((1u << i) - 1u)] ^= 1u << i;
    for (int i = 0; i < N; ++i) ans2 ^= w[i][dep & ((1u << i) - 1u)];
    for (auto y : Graph[x]) ans2 ^= Dfs(y, dep + 1);
    for (int i = 0; i < N; ++i) ans2 ^= w[i][dep & ((1u << i) - 1u)];
    return ans += ans2, ans2;
}
signed main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%u", a + i);
    for (int i = 2, p; i <= n; ++i) scanf("%d", &p), Graph[p].emplace_back(i);
    Dfs(1, 0u);
    return printf("%llu\n", ans), 0;
}