#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
static constexpr int N = 1e6 + 5;
int n, q, f[N], mark[N];
signed main() {
    freopen("food.in", "r", stdin);
    freopen("food.out", "w", stdout);
    scanf("%d%d", &n, &q);
    std::vector<int> s1, s2;
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        s1.emplace_back(n / i);
        s2.emplace_back(n / i);
    }
    s1.erase(std::unique(all(s1)), s1.end());
    s2.erase(std::unique(all(s2)), s2.end());
    std::reverse(all(s2));
    while (q--) {
        static int x;
        scanf("%d", &x);
        if (!mark[x]) for (auto i : s1) f[i] -= f[i / x];
        else for (auto i : s2) f[i] += f[i / x];
        mark[x] ^= 1;
        printf("%d\n", n - f[n]);
    }
    return 0;
}