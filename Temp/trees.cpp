#include <bits/stdc++.h>
static constexpr int N = 1e6 + 5, P = 1e9 + 7;
int n, m, ans = 1;
int s[N], f[N];
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
template<int N, int size>
class St_Table {
    private: int f[N][size];
    public: void Init(int n, int *a) {
        for (int i = 1; i <= n; ++i) f[i][0] = a[i];
        for (int j = 1; j <= size; ++j)
            for (int i = 1; i <= n - (1ll << j) + 1; ++i)
                f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        return void();
    }
    public: int Query(int l, int r) {
        int k = std::log2(r - l + 1);
        return std::min(f[l][k], f[r - (1 << k) + 1][k]);
    }
};
St_Table<N, 31> rmq;
std::set<int> pos[N];
int solve(int l, int r) {
    if (r <= l) return 1;
    int ret = 1, cnt = 0, min = rmq.Query(l, r), last = l;
    auto p = pos[min].lower_bound(l);
    while (p != pos[min].end() && *p <= r) {
        ++ cnt;
        ret = 1ll * ret * solve(last, (*p) - 1) % P;
        last = *p;
        ++ p;
    }   
    ret = 1ll * ret * solve(last + 1, r) % P;
    ret = 1ll * ret * f[cnt] % P;
    return ret;
}
signed main() {
    freopen("trees.in", "r", stdin);
    freopen("trees.out", "w", stdout);
    scanf("%d", &n);    
    for (int i = 1; i <= n; ++i) scanf("%d", s + i);
    for (int i = 1; i <= n; ++i) pos[s[i]].emplace(i);
    
    f[0] = 1;
    for (int i = 1; i <= n; ++i) 
        f[i] = 1ll * f[i - 1] * ((4ll * i % P + P - 2) % P) % P * qpow(i + 1, P - 2, P) % P;

    rmq.Init(n, s);
    return printf("%d\n", solve(1, n)), 0;
    
}