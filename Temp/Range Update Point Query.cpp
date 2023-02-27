#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 200'005;

int n, q;
int a[N][10], s[N];

int lowbit(int x)
{
    return x & (-x);
}

void add(int x, int v)
{
    for (; x <= n; x += lowbit(x))
        s[x] += v;
    return void();
}

int ask(int x)
{
    int ans = 0;
    for (; x >= 1; x -= lowbit(x))
        ans += s[x];
    return ans;
}

int calc(int x)
{
    int tmp = 0;
    while (x)
    {
        tmp += x % 10;
        x /= 10;
    }
    return tmp;
}

void solve()
{
    fscanf(fin, "%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", &a[i][0]);
    for (int i = 1; i <= n; ++i)
        s[i] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= 5; ++j)
            a[i][j] = calc(a[i][j - 1]);
    while (q--)
    {
        int opt, l, r, x;
        fscanf(fin, "%d", &opt);
        if (opt == 1)
        {
            fscanf(fin, "%d%d", &l, &r);
            add(l, 1);
            add(r + 1, -1);
        }
        if (opt == 2)
        {
            fscanf(fin, "%d", &x);
            int p = std::min(ask(x), 5);
            fprintf(fout, "%d\n", a[x][p]);
        }
    }
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    int t;
    fscanf(fin, "%d", &t);
    while (t--)
        solve();
    return 0;
}