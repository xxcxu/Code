#include <bits/stdc++.h>
static constexpr int P = 1e9 + 7;
int n, k, m, R, ans, bit[1 << 4];
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
int count(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ++ ans;
    return ans;
}
int id(int x, int y) {return x * (R + 1) + y;}
void cadd(int &x, int y) {x = (x + y) % P;}
signed main() {
    scanf("%d%d%d", &n, &k, &m);
    R = (1 << m) - 1;
    Matrix base = Matrix(id(k, R + 1), id(k, R + 1));
    for (int i = 1; i <= R; ++i) bit[i] = count(i);
    for (int i = 0; i <= k; ++i)
        for (int sta = 0; sta <= R; ++sta) {
            int s1 = sta >> 1, s2 = s1 | (1 << m - 1);
            if (sta + 1 & 1) {
                ++ base[id(i, sta)][id(i, s1)];
                ++ base[id(i, sta)][id(i, s2)];
            } else if (i) {
                base[id(i, sta)][id(i - 1, s1)] += bit[s1] + 1;
                base[id(i, sta)][id(i - 1, s2)] += bit[s2] + 1;
            }
        }
    base = base ^ n;
    for (int i = 0; i <= R; ++i) cadd(ans, base[id(k, i)][0]);
    return printf("%d\n", ans), 0;
}