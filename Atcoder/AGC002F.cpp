# include <bits/stdc++.h>

int read() {
    int t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}

static const int N = 2005, K = 2005, P = 1000000007;

int n = read(), k = read();
int fac[N * K], inv[N * K], dp[N][K];

int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}

int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x)) if (y & 1) ans = mul(ans, x);
    return ans % P;
}

void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2, P);
    for (int i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    return void();
}

int binom(int n, int m) {
    if (n < m || m < 0) return 0;
    return mul(fac[n], mul(inv[m], inv[n - m]));
}

int solve(int n, int k) {
    if (k == 1) return 1;
    init(n * k);
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= i; ++j) {
            if (j < i) dp[i][j] = inc(dp[i][j], dp[i - 1][j]);
            if (j) dp[i][j] = inc(dp[i][j], mul(binom(n * k - (j - 1) * (k - 1) - i - 1, k - 2), dp[i][j - 1]));
        }
    return mul(fac[n], dp[n][n]);
}

signed main() {
    printf("%d\n", solve(n, k));
    return 0;
} 