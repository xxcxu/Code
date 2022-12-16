#include <bits/stdc++.h>
#define int long long
int a, b, p, k;
int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % p)
        if (y & 1) ans = 1ll * ans * x % p;
    return ans;
}
int inv(int x) {return qpow(x, p - 2);}
int f(int x, int y) {
    long long ret = 1ll * a * b + 1ll * x * y;
    if (ret % p == 0) return 1;
    else {
        long long mul = 1ll * a * x + 1ll * b * y;
        return 1ll * mul % p * inv(ret % p) % p;
    }
}
signed main() {
    freopen("eglen.in", "r", stdin);
    freopen("eglen.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &a, &b, &p, &k);
    if (k >= a) {
        int now = 1;
        for (int i = a - 1; i >= 1; --i) now = f(now, i);
        printf("%lld\n", now);
    } else {
        int now = k;
        for (int i = k - 1; i >= 1; --i) now = f(now, i);
        printf("%lld\n", now);
    }
    return 0;
}