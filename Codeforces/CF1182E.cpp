#include <bits/stdc++.h>
#define int long long
const int mod = 1e9 + 7;
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
                for (int k = 0; k < a.m; ++k) ans.a[i][j] = (ans.a[i][j] + 1ll * a.a[i][k] * b.a[k][j] % (mod - 1)) % (mod - 1);
        return ans;
    }
    public: void print() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                printf("%lld%c", a[i][j], ' ');
            puts("");
        } return void();
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
int qpow(int x, int y, int mod) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % mod)
        if (y & 1) ans = 1ll * ans * x % mod;
    return ans % mod;
}
int n, f1, f2, f3, c, ans;
Matrix base1(5, 5), base2(3, 3), x(1, 5), x2(1, 3);
void Init() {
    base1[0][0] = base1[1][0] = base1[2][0] = base1[0][1] = base1[1][2] = base1[3][3] = base1[4][3] = base1[4][4] = 1;
    base1[3][0] = 2; base1[4][0] = mod - 5;
    base2[0][0] = base2[1][0] = base2[2][0] = base2[0][1] = base2[1][2] = 1;
    x[0][4] = 1; x[0][3] = 3;
    x2[0][2] = 1;
}
signed main() {
    scanf("%lld%lld%lld%lld%lld", &n, &f1, &f2, &f3, &c); ans = 1; Init();
    ans = qpow(c, (x * (base1 ^ (n - 3)))[0][0], mod);
    ans = 1ll * ans * qpow(f1, (x2 * (base2 ^ (n - 3)))[0][0], mod) % mod; x2[0][2] = 0, x2[0][1] = 1;
    ans = 1ll * ans * qpow(f2, (x2 * (base2 ^ (n - 3)))[0][0], mod) % mod; x2[0][1] = 0, x2[0][0] = 1;
    ans = 1ll * ans * qpow(f3, (x2 * (base2 ^ (n - 3)))[0][0], mod) % mod; return printf("%lld\n", ans), 0;
}