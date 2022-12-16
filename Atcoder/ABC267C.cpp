#include <bits/stdc++.h>
using LL = long long;
 
const int N = 2e5 + 5;
LL sum1, sum2;
int n, m, a[N];
 
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= m; i++) {
        sum1 += a[i];
        sum2 += 1ll * a[i] * i;
    }
    LL max = sum2;
    for (int i = m + 1; i <= n; i++) {
        sum2 = sum2 - sum1 + 1ll * a[i] * m;
        sum1 = sum1 - a[i - m] + a[i];
        max = std::max(max, sum2);
    }
    printf("%lld\n", max);
    return 0;
}