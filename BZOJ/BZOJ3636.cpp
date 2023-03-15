#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

#define int long long

#define ep emplace
#define eb emplace_back

static const int N = 100'005, NL = 55;
int n, q, L;
int a[N], sum[N], ans[N];

struct Node
{
    int l, r, id;
    Node(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id) {}
};

int f[NL][N], g[NL][N];
int ask(int l, int r) { return sum[r] - sum[l - 1]; }

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

void initL(int l, int r)
{
    for (int i = 0; i <= L; ++i)
    {
        int s = r - i;
        g[i][s + 1] = 0;
        for (int j = r; j >= l; --j)
        {
            if (j > s)
                g[i][j] = 0;
            else
            {
                g[i][j] = g[i][j + 1];
                if (j + L - 1 <= s)
                    cmax(g[i][j], g[i][j + L] + ask(j, j + L - 1));
            }
        }
    }
}
void initR(int l, int r)
{
    for (int i = 0; i <= L; ++i)
    {
        int s = l + i;
        f[i][s - 1] = 0;
        for (int j = l; j <= r; ++j)
        {
            if (j < s)
                f[i][j] = 0;
            else
            {
                f[i][j] = f[i][j - 1];
                if (j - L + 1 >= s)
                    cmax(f[i][j], f[i][j - L] + ask(j - L + 1, j));
            }
        }
    }
}

void solve(int l, int r, std::vector<Node> &query)
{
    if (l > r)
        return void();
    if (query.empty())
        return void();
    int mid = (l + r) >> 1;
    initL(l, mid), initR(mid, r);
    std::vector<Node> q1, q2;
    for (auto [qL, qR, id] : query)
    {
        if (qL <= mid && mid <= qR)
        {
            cmax(ans[id], f[1][qR] + g[0][qL]);
            for (int j = 1; j <= L && mid + (L - j + 1) - 1 <= n && mid - j + 1 >= 1; ++j)
            {
                int ql = mid - (L - j + 1) + 1, qr = mid + j - 1;
                if (qL <= ql && qr <= qR)
                    cmax(ans[id], f[j][qR] + std::max(ask(ql, qr) + g[L - j + 1][qL], 0ll));
            }
            continue;
        }
        if (qR <= mid)
            q1.eb(qL, qR, id);
        else
            q2.eb(qL, qR, id);
    }
    solve(l, mid, q1), solve(mid + 1, r, q2);
    return void();
}

signed main()
{
    fin = stdin;
    fout = stdout;
    ferr = stderr;
    fscanf(fin, "%lld%lld", &n, &L);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%lld", a + i);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + a[i];
    fscanf(fin, "%lld", &q);
    std::vector<Node> query;
    for (int i = 1; i <= q; ++i)
    {
        static int l, r;
        fscanf(fin, "%lld%lld", &l, &r);
        query.eb(l, r, i);
    }
    solve(1, n, query);
    for (int i = 1; i <= q; ++i)
        fprintf(fout, "%lld\n", ans[i]);
    return 0;
}