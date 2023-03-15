#include <bits/stdc++.h>

#define eb emplace_back

FILE *fin, *fout, *ferr;
static const int N = 1'000'005;
int n, q, ans;
int v[N], p[N];
std::vector<int> e[N];

void dfs(int x, int now, int d)
{
    if (now > d)
        return void();
    ans += now ^ v[x];
    for (int y : e[x])
        if (y != p[x])
            dfs(y, now + 1, d);
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("tree.in", "r"), fout = fopen("tree.out", "w+");
    fscanf(fin, "%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        fscanf(fin, "%d", v + i);
    }
    for (int i = 2; i <= n; ++i)
    {
        fscanf(fin, "%d", p + i);
        e[p[i]].eb(i);
    }
    fscanf(fin, "%d", &q);

    while (q--)
    {
        static int x, d;
        fscanf(fin, "%d%d", &x, &d);
        ans = 0;
        dfs(x, 0, d);
        fprintf(fout, "%d\n", ans);
    }
    return 0;
}