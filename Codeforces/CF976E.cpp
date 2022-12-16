#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e5 + 5;
int n, A, B, ans, sum, del;
class node {
    public: int a, b, c;
    public: node(int a = 0, int b = 0, int c = 0):
        a(a), b(b), c(c) {}
} p[N];
signed main() {
    scanf("%lld%lld%lld", &n, &A, &B); B = std::min(B, n);
    for (int i = 1; i <= n; ++i) scanf("%lld%lld", &p[i].a, &p[i].b);
    for (int i = 1; i <= n; ++i) p[i].c = std::max(0ll, p[i].a - p[i].b);
    for (int i = 1; i <= n; ++i) sum += p[i].b;
    if (!B) printf("%lld\n", sum);
    else {
        std::sort(p + 1, p + n + 1, [&](const node &a, const node &b) {return a.c > b.c;});
        for (int i = 1; i <= B; ++i) del += p[i].c;
        for (int i = 1; i <= n; ++i) ans = std::max(ans, del - p[i >= B ? B : i].c + (p[i].a << A) - p[i].b);
        printf("%lld\n", sum + ans);
    }
    return 0;
}