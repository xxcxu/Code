#include <bits/stdc++.h>
#define int long long
int n, l, r, P;
int inc(int x, int y, int p) {return (x + y) % p;}
int dec(int x, int y, int p) {return (x + p - y) % p;}
int mul(int x, int y, int p) {return 1LL * x * y % p;}
int qpow(int x, int y, int p) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x, p)) if (y & 1) ans = mul(ans, x, p);
    return ans % p;
}
int inv(int x, int p) {return qpow(x, p - 2, p);}
void solve() {
    scanf("%lld%lld%lld%lld", &n, &l, &r, &P);
    
    if (P == 2) return printf("%lld\n", n + 1 & 1), void();
        
    int k2l = std::__gcd(n, P) != 1 ? 0 : qpow(n, qpow(2, l, P - 1), P);
    int Inv = inv(qpow(2, r - l, P), P);

    int t = 0;
    if (k2l == 1) t = qpow(2, r - l + 1, P);
    if (k2l != 1) {
        int power = std::__gcd(n, P) != 1 ? 0 : qpow(n, qpow(2, r + 1, P - 1), P);
        t = mul(dec(power, 1, P), inv(dec(k2l, 1, P), P), P);
    }

    if (n % 2 == 0) printf("%lld\n", t);
    if (n % 2 == 1) printf("%lld\n", mul(t, Inv, P));
}
signed main() {
    int t; scanf("%lld", &t);
    while (t--) solve();
    return 0;
}
