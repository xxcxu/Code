#include <bits/stdc++.h>
#define int long long
static constexpr int N = 5e3 + 5;
int n, a, b, day, c[N];
signed main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &a, &b);
    for (int i = 1; i <= n; ++i) scanf("%lld", c + i);
    std::sort(c + 1, c + n + 1, std::less<int>());
    for (int i = 1; i <= n; ++i) {
        a += b; ++ day;
        if (a >= c[i]) a -= c[i]; 
        else {
            int p = (c[i] + b - a - 1) / b;
            day += p;
            a = a + p * b - c[i];
        }
    }
    printf("%lld\n", day);
    return 0;
}