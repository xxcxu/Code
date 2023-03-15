#include <bits/stdc++.h>

int read()
{
    int t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar())
        t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}

static const int N = 3'005, P = 998'244'353;

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }
template <typename... Args>
int mul(int x, Args... args) { return mul(x, mul(args...)); }

int n;
int a[N][N], b[N][N], c[N][N];

struct Matrix
{
    int n, m;
    std::vector<std::vector<int>> a;
    Matrix(int n = 0, int m = 0, int p = 0) : n(n), m(m)
    {
        a.resize(n, std::vector<int>(m, 0));
        if (p)
            for (int i = 0; i < n; ++i)
                a[i][i] = 1;
    }
    std::vector<int> &operator[](int x) & { return a[x]; }
    const std::vector<int> &operator[](int x) const & { return a[x]; }
    friend Matrix operator*(const Matrix &a, const Matrix &b)
    {
        Matrix ans = Matrix(a.n, b.m);
        for (int i = 0; i < a.n; ++i)
            for (int j = 0; j < b.m; ++j)
                for (int k = 0; k < a.m; ++k)
                    ans.a[i][j] = (ans.a[i][j] + 1ll * a.a[i][k] * b.a[k][j] % P) % P;
        return ans;
    }
};

void solve()
{
    Matrix a, b, c;
    n = read();
    a = Matrix(n, n), b = Matrix(n, n), c = Matrix(n, n);
    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> random(0, P - 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            a[i - 1][j - 1] = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            b[i - 1][j - 1] = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            c[i - 1][j - 1] = read();
    bool flag = true;
    for (int T = 0; T < 5; ++T)
    {
        Matrix V = Matrix(1, n);
        for (int i = 0; i < n; ++i)
            V[0][i] = random(gen);
        Matrix V2 = V * a * b;
        Matrix V3 = V * c;
        for (int i = 0; i < V2.n; ++i)
            for (int j = 0; j < V2.m; ++j)
                if (V2[i][j] != V3[i][j])
                {
                    flag = false;
                    goto E;
                }
    E:
        if (!flag)
            break;
    }
    puts(flag ? "Yes" : "No");
    return void();
}

signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    int t;
    t = read();
    while (t--)
        solve();
    return 0;
}