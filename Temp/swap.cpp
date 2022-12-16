#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5;
int n, a[N], b[N];
std::vector<std::pair<int, int>> ans;
signed main() {
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) b[a[i]] = i;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == i) continue;
        int p = b[i], q = b[p]; 
        ans.emplace_back(p, q);
        b[i] = i, b[a[i]] = p;
        std::swap(a[a[p]], a[a[q]]);
    }
    printf("%d\n", (int)ans.size());
    for (auto it : ans) printf("%d %d\n", it.first, it.second);
}