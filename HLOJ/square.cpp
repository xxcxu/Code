#include <bits/stdc++.h>
__int128 a, b, c, x, h;
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? -x : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
template<typename T>
void write(T x) {
    if (x < 0) {x = -x; putchar('-');}
    if (x > 9) write(x / 10); putchar(x % 10 + '0');
}
__int128 gcd(__int128 a, __int128 b) {return !b ? a : gcd(b, a % b);}
void solve() {
    read(a, b);
    __int128 c = a * a, d = b;
    write(c / gcd(c, d) + d / gcd(c, d));
    puts("");
}
signed main() {
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}