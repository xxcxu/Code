# include <bits/stdc++.h>

# define int long long
# define eb emplace_back

static const int N = 2005, inf = 0x3f3f3f3f3f3f3f;

FILE *fin, *fout, *ferr;

void cmin(int &x, int y) {if (y < x) x = y;}
void cmax(int &x, int y) {if (y > x) x = y;}

using pii = std::pair<int, int>;

int n, m, S, T, K;
int f[N * 5][N];
std::vector<pii> e[N];

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%lld%lld%lld%lld%lld", &n, &m, &S, &T, &K);
    for (int i = 1; i <= m; ++i)
    {
        static int x, y, z;
        fscanf(fin, "%lld%lld%lld", &x, &y, &z);
        e[x].eb(y, z);
        e[y].eb(x, z);
    }
    std::memset(f, 0x3f, sizeof f);
    f[0][S] = 0;
    for (int t = 1; t <= 5 * m; ++t)
    {
        for (int i = 1; i <= n; ++i)
            for (auto [j, k] : e[i])
                cmin(f[t][i], f[t - 1][j] + k);
    }

    int p1 = f[3 * m][T] - f[m][T];
    int p2 = f[5 * m][T] - f[3 * m][T];

    int ans = 0;
    if (K >= m)
    {
        ans += (K - m) / (4 * m) * (p1 + p2) + f[m][T];
        ans += f[(K - m) % (4 * m) + m][T] - f[m][T];
    } else ans += f[K][T];
    fprintf(fout, "%lld\n", ans);
    return 0;
}