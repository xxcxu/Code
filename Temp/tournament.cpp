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
static constexpr int N = 1e3 + 5;
using pii = std::pair<int, int>;
int n, m, d[N], mat[N][N];
std::vector<pii> v; 
signed main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(d[i]);
    m = d[n] + 1;
    int l = 1, r = n;
    while (l <= r) {
        for (int i = d[l - 1] + 1; i <= d[l]; ++i)
            for (int j = i + 1; j <= d[r] + 1; ++j)
                v.emplace_back(i, j);
        ++ l; -- r;
    }
    printf("%d\n", (int)v.size());
    for (auto [i, j] : v) printf("%d %d\n", i, j);
    return 0;
}