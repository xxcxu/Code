#include <bits/stdc++.h>

using ll = long long;

FILE *fin, *fout, *ferr;

static const int N = 505;

int n, m;
ll ans;
int a[N], dis[N], F[N][N];
bool vis[N];

int inc(int x, int y) { return (x + y) % m; }
int dec(int x, int y) { return (x + m - y) % m; }
int mul(int x, int y) { return 1LL * x * y % m; }

int qpow(int x, int y)
{
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1)
            ans = mul(ans, x);
    return ans;
}

int f(int a, int b)
{
    return inc(qpow(a, b), qpow(b, a));
}

void prim()
{
    std::memset(dis, -1, sizeof dis);
    for (int i = 1; i <= n; ++i)
    {
        int p = -1;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && (p == -1 || dis[p] < dis[j]))
                p = j;
        vis[p] = true;
        if (i != 1)
            ans += dis[p];
        for (int j = 1; j <= n; ++j)
            dis[j] = std::max(dis[j], F[j][p]);
    }
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", a + i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            F[i][j] = i != j ? f(a[i], a[j]) : -1;
    prim();
    fprintf(fout, "%lld\n", ans);
    return 0;
}