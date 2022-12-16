#include <bits/stdc++.h>
using ll = long long;
static constexpr int N = 2e6 + 5, P = 998244353;
template<const int N>
class Exkmp {
    private: int n;
    private: char str[N];
    public: int z[N], p[N];
    public: auto InitZ(char *s, int n) -> void {
        this -> n = n; z[1] = n;
        for (int i = 0; i <= n; ++i) str[i] = s[i];
        for (int i = 2, l = 0, r = 0; i <= n; ++i) {
            if (i <= r) z[i] = std::min(z[i - l + 1], r - i + 1);
            while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) ++ z[i];
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        } return;
    }
    public: auto Match(char *t, int m) -> void {
        for (int i = 1, l = 0, r = 0; i <= m; ++i) {
            if (i <= r) p[i] = std::min(z[i - l + 1], r - i + 1);
            while (i + p[i] <= m && t[i + p[i]] == str[p[i] + 1]) ++ p[i];
            if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
        } return;
    }
};
namespace modint {
    ll Inc(ll x, ll y) {y = (y + P) % P; x += y - P; return x + (x >> 31 & P);}
    template<typename ...Args>
    ll Inc(ll x, Args ...args) {return Inc(x, Inc(args...));}
    void cInc(ll &x, ll y) {x = Inc(x, y);}
    template<typename ...Args>
    void cInc(ll &x, Args ...args) {x = Inc(x, args...);}
};
using namespace modint;
Exkmp<N> Lvalue, Rvalue;
int n, m, k; ll f[N], g[N];
char s[N], l[N], r[N];
auto Leq(int x, int len) -> bool {
    int p = Lvalue.p[x];
    if (len > ::n || p == ::n || l[p + 1] < s[x + p]) return true;
    return false;
}
auto Geq(int x, int len) -> bool {
    int p = Rvalue.p[x];
    if (len < ::m || p == ::m || r[p + 1] > s[x + p]) return true;
    return false;
}
auto Check(int n, int len) -> bool {return Leq(n, len) && Geq(n, len);}
auto main() -> decltype(0) {
    scanf("%s%s%s", s + 1, l + 1, r + 1);
    n = strlen(l + 1), m = strlen(r + 1), k = strlen(s + 1);
    Lvalue.InitZ(l, n); Rvalue.InitZ(r, m);
    Lvalue.Match(s, k); Rvalue.Match(s, k);
    f[0] = 1;
    for (int i = 0; i <= k; ++i) {
        if (i) modint::cInc(g[i], g[i - 1]), modint::cInc(f[i], g[i]);
        if (s[i + 1] == '0') {
            if (n == 1 && l[1] == '0') modint::cInc(f[i + 1], f[i]);
            continue;
        }
        if (n < m) modint::cInc(g[i + n + 1], f[i]), modint::cInc(g[i + m], -f[i]);
        if (Check(i + 1, n)) modint::cInc(f[i + n], f[i]);
        if (n != m && Check(i + 1, m)) modint::cInc(f[i + m], f[i]);
    }
    return printf("%lld\n", f[k]), 0;
}