#include <bits/stdc++.h>
static constexpr int N = 1e2 + 5, P = 1e9 + 7;
class Matrix {
    private: int n, m;
    public: std::vector<std::vector<int>> a;
    public: Matrix(int n = 0, int m = 0, int p = 0): n(n), m(m) {
        a.resize(n, std::vector<int>(m, 0));
        if (p) for (int i = 0; i < n; ++i) a[i][i] = 1;
    }
    public: std::vector<int>& operator [] (int x) & {return a[x];}
    public: const std::vector<int>& operator[](int x) const& {return a[x];}
    public: friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix ans = Matrix(a.n, b.m);
        for (int i = 0; i < a.n; ++i)
            for (int j = 0; j < b.m; ++j)
                for (int k = 0; k < a.m; ++k)
                    ans.a[i][j] = (ans.a[i][j] + 1ll * a.a[i][k] * b.a[k][j] % P) % P;
        return ans;
    }
    public: void Unit() {
        assert(n == m);
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) a[i][j] = (i == j);
        return void();
    }
    public: friend Matrix operator ^ (Matrix a, int k) {
        Matrix ans = Matrix(a.n, a.m, 1);
        for (; k; k >>= 1, a = a * a) if (k & 1) ans = ans * a;
        return ans;
    }
};
int n, m, k, tot;
int a[N], b[N], c[N];
int C2(int x) {return (1ll * x * (x - 1) / 2) % P;}
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
int add(int x, int y) {return (1ll * x + y) % P;}
signed main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) if (!a[i]) ++ m;
    for (int i = 1; i <= m; ++i) if (!a[i]) ++ tot;
    Matrix base(m + 1, m + 1), F(m + 1, 1);
    if (m == 0 || m == n) return puts("1"), 0;
    int t1 = C2(m), t2 = C2(n - m); 
    int inv = qpow(C2(n), P - 2, P);
    for (int i = 0; i <= m; ++i) {
        a[i] = 1ll * (m - i) * (m - i) % P;
        b[i] = 1ll * i * (add(n - m, P - m + i)) % P;
        c[i] = ((C2(n) - a[i] - b[i]) % P + P) % P;
    }
    for (int i = 0; i <= m; ++i) {
        base[i][i] = c[i];
        if (i != m) base[i + 1][i] = a[i];
        if (i != 0) base[i - 1][i] = b[i];
    }
    F[tot][0] = 1;
    F = (base ^ k) * F;
    printf("%lld\n", 1ll * F[m][0] * qpow(inv, k, P) % P);
}