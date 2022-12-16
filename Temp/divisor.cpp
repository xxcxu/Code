#include <bits/stdc++.h>
#define eb emplace_back
int n;
std::unordered_map<int, int> map;
using uit = std::unordered_map<int, int>::iterator;
int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x *= x) if (y & 1) ans *= x;
    return ans;
}
void dfs(uit it, int redius, int op) {
    if (it == map.end()) return printf("%d ", redius), void();
    int p = it -> first, q = it -> second;
    auto it2 = it; ++ it2;
    if (op) for (int i = 0; i <= q; ++i) dfs(it2, redius * qpow(p, i), op ^ (i & 1));
    else for (int i = q; i >= 0; --i) dfs(it2, redius * qpow(p, i), op ^ (i & 1));
}
void solve() {
    scanf("%d", &n); int m = n; map.clear();
    for (int i = 2; i * i <= m; ++i) {
        if (m % i) continue;
        while (!(m % i)) m /= i, ++ map[i];
    }
    if (m != 1) ++ map[m];
    int ans = 1;
    for (auto it : map) ans *= it.second + 1;
    printf("%d\n", ans);
    dfs(map.begin(), 1, 1);
    puts("");
}
signed main() {
    freopen("divisor.in", "r", stdin);
    freopen("divisor.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve(); 
}
