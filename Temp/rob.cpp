#include <bits/stdc++.h>
static constexpr int N = 1 << 25;
int n, k, a[N];
signed main() {
    freopen("rob.in", "r", stdin);
    freopen("rob.out", "w", stdout);
    scanf("%d%d", &n, &k);
    if (n & 1 || k == n) puts("-30");
    else {
        k = std::min(k, n - k);
        int m = (n / 2) % k;
        if ((m & 1) == (k & 1)) {
            for (int i = 1; i + k <= n / 2; i += k) a[i] = 1;
            a[(n / 2 - m + 1) - (k - m) / 2] = 1;
            for (int i = 1; i <= n; ++i) printf("%d", a[i]);
        } else if (k & 1) for (int i = 1; i <= n; ++i) printf("%d", i & 1);
        else puts("-30");
    }
    return 0;
}