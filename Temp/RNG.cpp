#include <bits/stdc++.h>
static constexpr int P = 998244353;
int n, k;
int a[N], f[N], g[N], h1[N], h2[N], fac[N], inv[N], finv[N];
char s[N];
int Rev(int x) {return (x % P + P) % P;}
int Add(int x, int y) {x = Rev(x), y = Rev(y); return (x + y) % P;}
template<typename ...Args>
int Add(int x, Args ...args) {return Add(x, Add(args...));}
void cAdd(int &x, int y) {x = Add(x, y);}
template<typename ...Args>
void cAdd(int &x, Args ...args) {x = Add(x, args...);}
int Mul(int x, int y) {x = Rev(x), y = Rev(y); return 1ll * x * y % P;}
template<typename ...Args>
int Mul(int x, Args ...args) {return Mul(x, Mul(args...));}
void cMul(int &x, int y) {x = Mul(x, y);}
template<typename ...Args>
void cMul(int &x, Args ...args) {x = Mul(x, args...);}
void Init() {
    fac[0] = fac[1] = inv[1] = finv[0] = finv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fac[i] = Mul(fac[i - 1], i);
        inv[i] = Mul((P - P / i), inv[P % i]);
        finv[i] = Mul(finv[i - 1], inv[i]);
    } return void();
}
int C(int n, int m) {return Mul(fac[n], finv[m], finv[n - m]);}
int calc() {
    int res = pow10[n] * f[n] % P;
    if (k == 1) return res;
    for (int r = 1; r <= n - 1; ++r) cAdd(res, mul(pow10[r], f[r], h1[n - r - 1]));
    for (int l = 2; l <= n; ++l) cAdd(res, mul(pow10[n], Add(f[n], P - f[l - 1]), h1[l - 2]));
    if (k == 2) return res;
    for (int len = 1; len <= n - 2; ++len)
        cAdd(res, Mul(h2[n - len - 2], Add(g[n - 1], -g[len], -Mul(pow10[len], g[n - len - 1]))));
    return res;
}
signed main() {
    pow10[0] = 1;
    for (int i = 1; i < N; ++i) pow10[i] = Mul(pow10[i - 1], 10);
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%d%s", &k, s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) a[i] = s[i] - '0';
        for (int i = 1; i <= n; ++i) h1[i] = h2[i] = 0;
        int inv10 = inv[10];
        for (int i = 1; i <= n; ++i) {
            f[i] = Add(f[i - 1], Mul(inv10, a[i]));
            cMul(inv10, inv[10]);
        }
        for (int i = 1; i <= n; ++i)
            g[i] = Add(g[i - 1], Mul(pow10[i], f[i]));
        h1[0] = h2[0] = 1;
        if (k >= 2) for (int i = 1; i <= n; ++i) h1[i] = Add(Mul(h1[i - 1], 2), P - C(i - 1, k - 2));
        if (k >= 3) for (int i = 1; i <= n; ++i) h2[i] = Add(Mul(h2[i - 1], 2), P - C(i - 1, k - 3));
        printf("%d\n", calc());
    }
    return 0; 