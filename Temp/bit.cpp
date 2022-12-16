#include <bits/stdc++.h>
using ll = long long;
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
static constexpr int N = 1e5 + 5, M = 1 << 20;
int n, m, q, ans;
int a[N], cnt[M + 1];
std::vector<int> v1;
int And(int x, int y) {return x & y;}
int Xor(int x, int y) {return x ^ y;}
int Or(int x, int y) {return x | y;}
ll count(int x, int y) {
    if (v1[x] == v1[y]) return 1ll * cnt[v1[x]] * (cnt[v1[x]] - 1) / 2;
    return 1ll * cnt[v1[x]] * cnt[v1[y]];
}
void solve(auto foo) {
    int ans = 0; ll tot = 0;
    for (int i = 0; i < (int)v1.size(); ++i)
        for (int j = i; j < (int)v1.size(); ++j) 
            if (i != j || cnt[v1[i]] > 1) {
                if (foo(v1[i], v1[j]) > ans) ans = foo(v1[i], v1[j]), tot = count(i, j);
                else if (foo(v1[i], v1[j]) == ans) tot += count(i, j);
            }
    printf("%d %lld\n", ans, tot);
}
signed main() {
    freopen("bit.in", "r", stdin);
    freopen("bit.out", "w", stdout);
    read(n, q);
    for (int i = 1; i <= n; ++i) read(a[i]), m = std::max(m, a[i]);
    for (int i = 1; i <= n; ++i) {
        ++ cnt[a[i]];
        if (cnt[a[i]] == 1) v1.emplace_back(a[i]);
    }
    if (q == 1) solve(And);
    if (q == 2) solve(Xor);
    if (q == 3) solve(Or);
}