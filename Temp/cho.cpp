#include <bits/stdc++.h>
#define int long long
using ull = unsigned long long;
static const int N = 205, M = 100005, P = 9963, inf = 1e15;
int n, m, ans, l[N], a[N][N];
ull h[N][M], p[M];
std::string s[N];
ull hash(int i, int l, int r) {return h[i][r] - h[i][l - 1] * p[r - l + 1];}
class Matrix {
    private: int n, m;
    public: std::vector<std::vector<int>> a;
    public: Matrix(int n = 0, int m = 0, int p = 0): n(n), m(m) {
        a.resize(n, std::vector<int>(m, 0));
        if (p) for (int i = 0; i < n; ++i) a[i][i] = inf;
    }
    public: std::vector<int>& operator [] (int x) & {return a[x];}
    public: const std::vector<int>& operator[](int x) const& {return a[x];}
    public: friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix ans = Matrix(a.n, b.m);
        for (int i = 0; i < a.n; ++i)
            for (int j = 0; j < b.m; ++j) {
                ans.a[i][j] = inf;
                for (int k = 0; k < a.m; ++k)
                    ans.a[i][j] = std::min(ans.a[i][j], a.a[i][k] + b.a[k][j]);
            }
        return ans;
    }
    public: friend Matrix operator ^ (Matrix a, int k) {
        Matrix ans = a; -- k;
        for (; k; k >>= 1, a = a * a) if (k & 1) ans = ans * a;
        return ans;
    }
};
signed main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> s[i];
    for (int i = 1; i <= n; ++i) s[i] = " " + s[i];
    for (int i = 1; i <= n; ++i) l[i] = (int)s[i].length() - 1;
    
    p[0] = 1;
    for (int i = 1; i <  N; ++i) p[i] = p[i - 1] * P;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= l[i]; ++j) h[i][j] = h[i][j - 1] * P + s[i][j];
    
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (i != j)
                for (int k = 1; k <= l[i] && k <= l[j]; ++k)
                    if (hash(i, l[i] - k + 1, l[i]) == hash(j, 1, k)) a[i][j] = k;
            else
                for (int k = 1; k <  l[i]; ++k)
                    if (hash(i, l[i] - k + 1, l[i]) == hash(i, 1, k)) a[i][i] = k;

    Matrix base(n + 1, n + 1);
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) base[i][j] = l[j] - a[i][j];
    for (int i = 1; i <= n; ++i) base[0][i] = l[i];
    for (int i = 1; i <= n; ++i) base[i][0] = inf;
    base[0][0] = inf;

    base = base ^ m; int ans = inf;
    for (int i = 0; i <= n; ++i) ans = std::min(ans, base[0][i]);
    return printf("%lld\n", ans), 0;
}