#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 4'005, P = 1'000'000'007;

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }

int n, m;
struct Node
{
    int l, r;
} a[N];
struct TreeArray
{
    int s[N];
    int lowbit(int x) { return x & -x; }
    void add(int x, int v)
    {
        for (; x <= m; x += lowbit(x))
            s[x] = inc(s[x], v);
    }
    int ask(int x)
    {
        int ans = 0;
        for (; x; x -= lowbit(x))
            ans = inc(ans, s[x]);
        return ans;
    }
} f[N];

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%d", &n);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d%d", &a[i].l, &a[i].r);
    for (int i = 1; i <= n; ++i)
        ++a[i].l, ++a[i].r, m = std::max(m, a[i].r);
    std::sort(a + 1, a + n + 1, [&](Node &a, Node &b)
              { return std::tie(a.l, a.r) < std::tie(b.l, b.r); });
    for (int i = 1; i <= n; ++i)
    {
        for (int j = m; j >= a[i].l; --j)
            f[std::max(j, a[i].r)].add(std::min(j, a[i].r), f[j].ask(a[i].l - 1));
        f[a[i].r].add(1, 1);
    }
    int ans = 0;
    for (int i = 1; i <= m; ++i)
        ans = inc(ans, f[i].ask(m));
    fprintf(fout, "%d\n", ans);
    return 0;
}