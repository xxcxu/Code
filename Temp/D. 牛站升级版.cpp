#include <bits/stdc++.h>

#define int long long
#define eb emplace_back

static const int N = 1005, M = 2005, inf = 0x3f3f3f3f3f3f3f;

FILE *fin, *fout, *ferr;

void cmin(int &x, int y)
{
    if (y < x)
        x = y;
}
void cmax(int &x, int y)
{
    if (y > x)
        x = y;
}

using pii = std::pair<int, int>;

class Matrix
{
private:
    int n, m;

public:
    std::vector<std::vector<int>> a;

    Matrix(int n = 0, int m = 0, int p = 0) : n(n), m(m)
    {
        a.resize(n, std::vector<int>(m, inf));
    }

    std::vector<int> &operator[](int x) & { return a[x]; }

    const std::vector<int> &operator[](int x) const & { return a[x]; }

    friend Matrix operator*(const Matrix &a, const Matrix &b)
    {
        Matrix ans = Matrix(a.n, b.m);
        for (int i = 0; i < a.n; ++i)
            for (int j = 0; j < b.m; ++j)
            {
                ans.a[i][j] = inf;
                for (int k = 0; k < a.m; ++k)
                    ans.a[i][j] = std::min(ans.a[i][j], a.a[i][k] + b.a[k][j]);
            }
        return ans;
    }

    friend Matrix operator^(Matrix a, int k)
    {
        Matrix ans = a;
        k = k - 1;
        for (; k; k >>= 1, a = a * a)
            if (k & 1)
                ans = ans * a;
        return ans;
    }
};

int n, m, S, T, K;
int f[M * 7][N];
std::vector<pii> e[N];

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%lld%lld%lld%lld%lld", &n, &m, &S, &T, &K);
    if (n <= 100)
    {
        Matrix ans(1, n);
        Matrix base(n, n);
        for (int i = 1; i <= m; ++i)
        {
            static int x, y, z;
            fscanf(fin, "%lld%lld%lld", &x, &y, &z);
            cmin(base[x - 1][y - 1], z);
            cmin(base[y - 1][x - 1], z);
        }
        ans[0][S - 1] = 0;
        ans = ans * (base ^ K);
        fprintf(fout, "%lld\n", ans[0][T - 1]);
        return 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        static int x, y, z;
        fscanf(fin, "%lld%lld%lld", &x, &y, &z);
        e[x].eb(y, z);
        e[y].eb(x, z);
    }
    std::memset(f, 0x3f, sizeof f);
    f[0][S] = 0;
    for (int t = 1; t <= 7 * m; ++t)
    {
        for (int i = 1; i <= n; ++i)
            for (auto [j, k] : e[i])
                cmin(f[t][i], f[t - 1][j] + k);
    }

    int p1 = f[4 * m][T] - f[m][T];
    int p2 = f[7 * m][T] - f[4 * m][T];

    int ans = 0;
    if (K >= m)
    {
        ans += (K - m) / (6 * m) * (p1 + p2) + f[m][T];
        ans += f[(K - m) % (6 * m) + m][T] - f[m][T];
    }
    else
        ans += f[K][T];
    fprintf(fout, "%lld\n", ans);
    return 0;
}