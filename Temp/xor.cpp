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
static constexpr int N = 1e5 + 5;
int n, A, B, a[N], b[N], c[N];
void insert(int x) {
    for (int i = 60; ~i; --i) {
        if (!(x >> i & 1)) continue;
        if (c[i]) x ^= c[i];
        else return c[i] = x, void();
    }
}
void solve() {
    for (int i = 60; ~i; --i) {
        int ax = A >> i & 1, bx = B >> i & 1;
        if (ax && bx || !c[i]) continue;
        if (!ax && !bx) A ^= c[i], B ^= c[i];
        else {insert(c[i] ^ (1ll << i)); c[i] = 0; solve();}
    }
}
signed main() {
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), A ^= a[i];
    for (int i = 1; i <= n; ++i) read(b[i]), B ^= b[i];
    for (int i = 1; i <= n; ++i) insert(a[i] ^ b[i]);
    solve();
    printf("%lld\n", A + B);
    return 0;
} 