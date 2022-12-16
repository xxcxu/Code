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
using pii = std::pair<int, int>;
static constexpr int N = 1e6 + 5;
int n, inf, a[N];
pii f[N], g[N];
void merge(pii &a, pii b) {
    int l = std::max(a.first, b.first);
    int r = std::min(a.second, b.second);
    if (l > r) a = pii(0, -1);
    else a = pii(l, r);
}
signed main() {
    freopen("panic.in", "r", stdin);
    freopen("panic.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) inf = std::max(inf, a[i]);
    inf = inf * 2 + 1;
    f[0] = g[n + 1] = pii(0, inf);
    for (int i = 1; i <= n; ++i) {
        if (i == 1) f[i] = pii(0, inf);
        else if (a[i - 1] > a[i]) f[i] = pii(a[i - 1], a[i - 1] + a[i] - 1);
        else if (a[i - 1] < a[i]) f[i] = pii(a[i - 1] + a[i] + 1, inf);
        else f[i] = pii(-1, 0);
        merge(f[i], f[i - 1]);
    }   
    for (int i = n; i >= 1; --i) {
        if (i == n) g[i] = pii(0, inf);
        else if (a[i + 1] < a[i]) g[i] = pii(a[i + 1] + a[i] + 1, inf);
        else if (a[i + 1] > a[i]) g[i] = pii(0, a[i + 1] + a[i] - 1);
        else g[i] = pii(-1, 0);
        merge(g[i], g[i + 1]);  
    }
    for (int i = 0; i <= n; ++i) {
        merge(f[i], g[i + 1]);
        for (int k = f[i].first; k <= f[i].second; ++i) {
            if (std::min(a[i], k - a[i]) == std::max(a[i + 1], k - a[i + 1])) continue;
            printf("%d\n", k);
            for (int j = 1; j <= i; ++j) printf("%d ", std::min(a[j], k - a[j]));
            for (int j = i + 1; j <= n; ++j) printf("%d ", std::max(a[j], k - a[j]));
            return 0;
        }
    }
    puts("-1");
    return 0;
}