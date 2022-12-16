#include <bits/stdc++.h>
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
#define int long long
static constexpr int P = 1e9 + 9;
int n, d, m, ans = 1;
std::unordered_map<int, int> pd, pm;
int Gcd(int x, int y) {return !y ? x : Gcd(y, x % y);}
int Lcm(int x, int y) {return x / Gcd(x, y) * y;}
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = x * x % P)
        if (y & 1) ans = ans * x % P;
    return ans % P;
}
int solve(int max, int min) {
    if (max == min) return 1;
    return ((qpow(max - min + 1, n, P) + P - (2 * qpow(max - min, n, P) % P)) % P + qpow(max - min - 1, n, P)) % P;
}
signed main() {
    freopen("gcdlcm.in", "r", stdin);
    freopen("gcdlcm.out", "w", stdout);
    read(n, d, m);
    if (m % d != 0) return puts("0"), 0;
    for (int i = 2; i * i <= m; ++i) {
        if (m % i) continue;
        while (!(m % i)) m /= i, ++ pm[i];
    }
    if (m != 1) ++ pm[m];
    for (auto [fi, se] : pm) {
        while (!(d % fi)) d /= fi, ++ pd[fi];
        ans = ans * solve(se, pd[fi]) % P;
    }
    printf("%lld\n", ans);
    return 0;
}