#include <bits/stdc++.h>
static const int N = 1000005;
int n, A, B, ans = 0;
int a[N], L[N], R[N], lg2[N];   
class St_Table {
    private: int f[N][21], g[N][21];
    public: void init(int n, int *a) {
        for (int i = 1; i <= n; ++i) f[i][0] = g[i][0] = a[i];
        for (int j = 1; j <= 20; ++j)
            for (int i = 1; i <= n - (1ll << j) + 1; ++i)
                f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]),
                g[i][j] = std::max(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
        return void();
    }
    public: int ask1(int l, int r) {
        int k = lg2[r - l + 1];
        return std::max(g[l][k], g[r - (1 << k) + 1][k]);
    }
    public: int ask2(int l, int r) {
        int k = lg2[r - l + 1];
        return std::min(f[l][k], f[r - (1 << k) + 1][k]);
    }
};
St_Table st;
signed main() {
    lg2[1] = 0;
    scanf("%d%d%d", &n, &A, &B);
    for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1; 
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    st.init(n, a);
    for (int i = 1; i <= n; ++i) {
        L[i] = i;
        for (int j = 20; j >= 0; --j)
            if (L[i] - (1 << j) >= 1)
                if (st.ask1(L[i] - (1 << j), L[i]) <= a[i])
                    L[i] -= 1 << j;
    }
    for (int i = 1; i <= n; ++i) {
        R[i] = i;
        for (int j = 20; j >= 0; --j)
            if (R[i] + (1 << j) <= n)
                if (st.ask1(R[i], R[i] + (1 << j)) <= a[i])
                    R[i] += 1 << j;
    }
    for (int i = 1; i <= n; ++i) {
        int min1 = a[i] - A, min2 = a[i] - B;
        int l = i, r = i;
        for (int j = 20; j >= 0; --j)
            if (l - (1 << j) >= L[i]) 
                if (st.ask2(l - (1 << j), l) >= min2) l -= 1 << j;
        for (int j = 20; j >= 0; --j)   
            if (r + (1 << j) <= R[i]) 
                if (st.ask2(r, r + (1 << j)) >= min2) r += 1 << j;
        if (st.ask2(l, r) <= min1) ans = std::max(ans, r - l + 1);
    }
    printf("%d\n", ans);
    return 0;
}