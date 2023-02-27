#include <bits/stdc++.h>

#define eb emplace_back

FILE *fin, *fout, *ferr;

static const int N = 200'005, P = 998'244'353;

int n, m;
int a[N];
std::vector<int> prime;

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }

void pcalc(int x)
{
    for (int i = 2; i * i <= x; ++i)
    {
        if (x % i == 0)
            prime.eb(i);
        while (x % i == 0)
            x /= i;
    }
    if (x != 1)
        prime.eb(x);
    return void();
}

void solve()
{
    fscanf(fin, "%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%d", a + i);
    int ans = (m >= a[1]);
    for (int i = 2; i <= n; ++i)
    {
        if (a[i] > a[i - 1] || a[i - 1] % a[i] != 0)
        {
            ans *= 0;
            break;
        }
        if (a[i] == a[i - 1])
        {
            ans = mul(ans, m / a[i]);
        }
        else
        {
            int res = 0;
            int t = a[i - 1] / a[i];
            prime.clear();
            pcalc(t);
            int S = prime.size();
            for (int j = 0; j < (1 << S); ++j)
            {
            
                int cnt = 0, factor = 1;
                for (int k = 0; k < S; ++k)
                    if (j >> k & 1)
                        ++cnt, factor *= prime[k];
                res = cnt & 1 ? dec(res, m / a[i] / factor) : inc(res, m / a[i] / factor);
            }
            ans = mul(ans, res);
        }
    }
    fprintf(fout, "%d\n", ans);
    return void();
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