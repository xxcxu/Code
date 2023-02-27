#include <bits/stdc++.h>

static const int N = 400005, P = 998244353;
int n, k;
int cnt[N], fac[N], inv[N];
FILE *fin, *fout, *ferr;

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
void init(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = mul(inv[i + 1], i + 1);
    return void();
}
int binom(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return mul(mul(fac[n], inv[m]), inv[n - m]);
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%d%d", &n, &k);
    init(n + k);
    for (int i = 1; i <= n; ++i)
    {
        static int x;
        fscanf(fin, "%d", &x);
        if (x <= n + k)
            ++cnt[x];
    }

    int cur = 0, ans = 0;
    for (int i = 0; i <= n + k; ++i)
    {
        ans = inc(ans, binom(k - cur + i - 1, k - cur - 1));
        cur += cnt[i] == 0;
    }
    fprintf(fout, "%d\n", ans);
    return 0;
}