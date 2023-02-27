# include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

static const int N = 2005, P = 998244353;

int n, m, k;
int fac[N], inv[N], dow[N], s[N][N];

int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}

int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1) ans = mul(ans, x);
    return ans;
}

void init(int N) {
    fac[0] = 1;
    for (int i = 1; i <= N; ++i) fac[i] = mul(fac[i - 1], i);
    inv[N] = qpow(fac[N], P - 2);
    for (int i = N - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    s[0][0] = 1;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= i; ++j)
            s[i][j] = inc(mul(s[i - 1][j], j), s[i - 1][j - 1]);
    return void();
}

void solve() {
    fscanf(fin, "%d%d%d", &n, &m, &k);
    dow[0] = 1;
    for (int i = 1; i <= k && i <= n; ++i) dow[i] = mul(dow[i - 1], n - i + 1);
    int ans = 0;
    for (int i = 0; i <= k && i <= n; ++i) {
        ans = inc(ans, mul(mul(s[k][i], dow[i]), mul(qpow((m + 1) / 2, i), qpow(m, n - i))));
    }
    fprintf(fout, "%d\n", ans);
    return void();
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    init(N - 1);
    int t;
    fscanf(fin, "%d", &t);
    while (t--)
        solve();
    return 0;
}