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
static constexpr int N = 1e6 + 5;
#define int long long
int P, S, cnt;
char* build(int n, int m) {
    static char str[N];
    for (int i = 1; i <= n; ++i) str[cnt ++] = '2';
    str[cnt ++] = '3';
    for (int i = 1; i <= m - 1; ++i) str[cnt ++] = '2';
    str[cnt ++] = '3';
    for (int i = 1; i <= n - 1; ++i) str[cnt ++] = '2';
    str[cnt ++] = '3';
    for (int i = 1; i <= m - 1; ++i) str[cnt ++] = '2';
    return str;
}
bool check(int n, int m) {
    if (2 * (n + m) == P && n * m == S) return true;
    return false;
}
using pii = std::pair<int, int>;
pii solve() {
    #define eb emplace_back
    std::vector<int> factor;
    for (int i = 1; i * i <= S; ++i) {
        if (!(S % i)) factor.eb(i);
        if (i * i != S) factor.eb(S / i);
    }
    for (auto i : factor)
        if (check(i, S / i)) return pii(i, S / i);
    return pii(-1, -1);
    #undef eb
}

signed main() {
    freopen("run.in", "r", stdin);
    freopen("run.out", "w", stdout);
    read(P, S);
    auto [n, m] = solve();
    if (n == -1 && m == -1) puts("Impossible");
    else puts(build(n, m));
}