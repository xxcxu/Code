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
static constexpr int N = 1e5 + 5;
int n, a[N];
double ans;
signed main() {
    freopen("ill.in", "r", stdin);
    freopen("ill.out", "w", stdout);
    read(n); 
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 2; i <= n; ++i) ans += 1.0 * a[i] / (a[i] + a[1]);
    printf("%.3lf\n", ans + 1);
    return 0;
}