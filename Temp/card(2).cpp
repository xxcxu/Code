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
static constexpr int N = 1e2 + 5, P = 998244353;
int n, k, p[N], q[N], f[N];
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
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
    public: friend Matrix operator ^ (Matrix a, int k) {
        Matrix ans = Matrix(a.n, a.m, 1);
        for (; k; k >>= 1, a = a * a) if (k & 1) ans = ans * a;
        return ans;
    }
};
signed main() {
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    read(n, k);
    for (int i = 1; i <= k; ++i) {
        static int a, b;
        read(a, b);
        p[i] = 1ll * a * qpow(b, P - 2, P) % P;
    } p[k + 1] = 1;
    for (int i = 1; i <= k; ++i) {
        int prod = 1;
        for (int j = 1; j <= i; ++j) {
            f[i] = (f[i] + 1ll * prod * p[j] % P * (f[i - j] + 1) % P) % P;
            prod = 1ll * prod * (P - p[j] + 1) % P;
        }
    }
    if (n <= k) return printf("%d\n", f[n]), 0;

    Matrix F(1, k + 2), Base(k + 2, k + 2);
    F[0][0] = 1;
    for (int i = 0; i <= k; ++i) F[0][i + 1] = f[i];
    Base[0][0] = Base[0][k + 1] = 1;
    for (int i = 2; i <= k + 1; ++i) Base[i][i - 1] = 1;
    q[1] = 1;
    for (int i = 2; i <= k + 1; ++i) q[i] = 1ll * q[i - 1] * (P + 1 - p[i - 1]) % P;
    for (int i = 1; i <= k + 1; ++i) q[i] = 1ll * q[i] * p[i] % P;
    for (int i = 1; i <= k + 1; ++i) Base[i][k + 1] = q[k - i + 2];
	F = F * (Base ^ (n - k));
    printf("%d\n", F[0][k + 1]);
	return 0;
}