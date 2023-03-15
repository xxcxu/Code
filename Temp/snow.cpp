#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 100'005, P = 998'244'353, inf = N;

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }
int qpow(int x, int y)
{
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1)
            ans = mul(ans, x);
    return ans;
}
int inv(int x) { return qpow(x, P - 2); }

int n, m, T, a[N], b[N][50], c[N][50];
int bel[N], L[N], R[N], tag[N], all_tag[N];
bool equal[N];

int id(int x)
{
    return x < 24 ? x : (x - 24) % 24 + 24;
}

void init()
{
    T = std::sqrt(n);
    for (int i = 1; i <= n; ++i)
        bel[i] = (i - 1) / T + 1;
    for (int i = 1; i <= bel[n]; ++i)
        L[i] = inf, R[i] = -inf, equal[i] = true;
    for (int i = 1; i <= n; ++i)
        L[bel[i]] = std::min(L[bel[i]], i);
    for (int i = 1; i <= n; ++i)
        R[bel[i]] = std::max(R[bel[i]], i);
    for (int i = 1; i <= bel[n]; ++i)
        for (int j = L[i]; j <= R[i]; ++j)
            for (int k = 0; k <= 47; ++k)
                c[i][k] = inc(c[i][k], b[j][k]);
    return void();
}
void add(int l, int r)
{
    int p = bel[l], q = bel[r];
    if (p == q)
    {
        if (l == L[p] && r == R[p])
            ++all_tag[p];
        else
            for (int i = l; i <= r; ++i)
                ++tag[i];
        equal[p] &= (l == L[p] && r == R[p]);
    }
    else
    {
        equal[p] &= (l == L[p]);
        equal[q] &= (r == R[q]);
        if (l == L[p])
            ++all_tag[p];
        else
            for (int i = l; i <= R[p]; ++i)
                ++tag[i];
        if (r == R[q])
            ++all_tag[q];
        else
            for (int i = L[q]; i <= r; ++i)
                ++tag[i];
        for (int i = p + 1; i < q; ++i)
            ++all_tag[i];
    }
    return void();
}
int ask(int l, int r)
{
    int p = bel[l], q = bel[r];
    if (p == q)
    {
        int ans = 0;
        for (int i = l; i <= r; ++i)
            ans = inc(ans, b[i][id(tag[i] + all_tag[p])]);
        return ans;
    }
    else
    {
        int ans = 0;
        for (int i = l; i <= R[p]; ++i)
            ans = inc(ans, b[i][id(tag[i] + all_tag[bel[i]])]);
        for (int i = L[q]; i <= r; ++i)
            ans = inc(ans, b[i][id(tag[i] + all_tag[bel[i]])]);
        for (int i = p + 1; i < q; ++i)
        {
            if (!equal[i])
                for (int j = L[i]; j <= R[i]; ++j)
                    ans = inc(ans, b[j][id(tag[j] + all_tag[i])]);
            if (equal[i])
                ans = inc(ans, c[i][id(all_tag[i])]);
        }
        return ans;
    }
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("snow.in", "r");
    fout = fopen("snow.out", "w+");
    fscanf(fin, "%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", a + i);
    for (int i = 1; i <= n; ++i)
    {
        b[i][0] = inv(a[i]);
        for (int j = 1; j <= 47; ++j)
            b[i][j] = mul(b[i][j - 1], b[i][j - 1]);
    }
    init();

    for (int i = 1; i <= m; ++i)
    {
        static int opt, l, r;
        fscanf(fin, "%d%d%d", &opt, &l, &r);
        if (opt == 0)
            add(l, r);
        if (opt == 1)
            fprintf(fout, "%d\n", ask(l, r));
    }
    return 0;
}