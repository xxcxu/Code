#include <bits/stdc++.h>
#define int long long
const int N = 5e3 + 5; int n, k, h[N], f[N];
const double eps = 1e-6;
int calc(int i, int j) {return (j - i) * (j - i) + (h[i] - h[j]) * (h[i] - h[j]);}
bool check(int x, int y) {
    double h1 = h[x], kk = 1.0 * (h[y] - h[x]) / (y - x);
    for (int i = x + 1; i < y; ++i) {
        h1 += kk;
        if (h1 < h[i] && fabs(h1 - h[i]) > eps) return false;
    } return true;
}
signed main() {
    scanf("%lld%lld", &n, &k); std::fill(f + 1, f + n + 1, 1e9 + 7);
    for (int i = 1; i <= n; ++i) scanf("%lld", h + i);
    f[1] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = i - 1; j; --j)
            if (f[j] + 1 < f[i] && check(j, i)) f[i] = std::min(f[i], f[j] + 1);
    return printf("%lld\n", f[n] - 2), 0;
}