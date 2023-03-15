#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
#define eb emplace_back
#define all(x) x.begin(), x.end()

FILE *fin, *fout, *ferr;

static const int N = 200'005;
static const LD eps = 1e-8;

int n, a[N], b[N];
LL k, c;
LD s[N], t[N];

bool check(LD x)
{
    LL cnt = 0;
    for (int i = 1, j = 1; i <= n; ++i)
    {
        s[i] = s[i - 1] + std::max(a[i] - b[i] * x, (LD)0.0);
        while (j <= i && s[i] - s[j - 1] > c * x)
            ++j;
        cnt += i - j + 1;
    }
    return cnt >= k;
}

signed main()
{
    fin = fopen("fraction.in", "r");
    fout = fopen("fraction.out", "w+");
    ferr = stderr;

    fscanf(fin, "%d%lld%lld", &n, &k, &c);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", a + i);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", b + i);
    LD l = 0.0, r = 1.0;
    while (r - l > eps)
    {
        LD mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    return fprintf(fout, "%Lf\n", r), 0;
}