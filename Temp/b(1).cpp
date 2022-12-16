#include <bits/stdc++.h>
#define eb emplace_back
using ll = long long;
int n;
ll sqr3(int x) {return 1ll * x * x * x;}
void solve() {
    scanf("%d", &n);
    if (n % 3 == 0) printf("%lld\n", sqr3(n / 3));
    if (n % 3 == 1) {
        if ((n / 3) % 4 == 1) printf("%lld\n", 1ll * (n / 2) * (n / 4) * (n / 4));
        else puts("-1");
    }
    if (n % 3 == 2) {
        if ((n / 3) % 4 == 2) printf("%lld\n", 1ll * (n / 2) * (n / 4) * (n / 4));
        else puts("-1");
    }
}
signed main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}