#include <bits/stdc++.h>
static constexpr int N = 6e5 + 5, P = 1e9 + 7;
int n, ans, a[N];
int mul(int x, int y) {return 1ll * x * y % P;}
int add(int x, int y) {return (x + y) % P;}
int lowbit(int x) {return x & -x;}
int f(int n);
int g(int n);
int f(int n) {
    if (!n) return mul(a[0], a[0]);
    int ret = mul(a[n], a[n]), res = 0;
    for (int i = (n - 1) & n; i; i = (i - 1) & n) res = add(res, g(i));
    res = add(res, g(0));
    return add(ret, mul(res, res));
}
int g(int n) {
    int res = 0;
    for (int i = n; i; i = (i - 1) & n) res = add(res, mul(f(i), f(i)));
    res = add(res, mul(f(0), f(0)));
    return res;
}
signed main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", a + i);
    for (int i = 0; i < n; ++i) ans = add(ans, mul(i, mul(f(i), g(i))));
    return printf("%d\n", ans), 0;
}