# include <bits/stdc++.h>

static const int N = 20000005, P = 1000000007;

int n;
int fac[N], inv[N];

int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}

int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1) ans = mul(ans, x);
    return ans % P;
}

void init(int n) {
    fac[0] = fac[1] = 1;
    for (int i = 2; i <= n; ++i) fac[i] = mul(fac[i - 2], i);
    inv[n] = qpow(fac[n], P - 2, P);
    inv[n - 1] = qpow(fac[n - 1], P - 2, P);
    for (int i = n - 2; i >= 0; --i) inv[i] = mul(inv[i + 2], i + 2);
}

signed main() {
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    scanf("%d", &n); 
    n *= 2; init(n * 2);
    int ans = 0;
    for (int i = 3; i <= 2 * n - 1; ++i) {
        int x = i - n - 1, y = (2 * n - i) / 2;
        if (x < 0) continue;
        int now = mul(qpow(x, y, P), fac[std::max(0, n - 2 * (y + 1) - 1)]);
        ans = inc(ans, mul(now, std::min((i - 1) / 2, n) - std::max(i - n, 1) + 1));
    }
    return printf("%d\n", mul(ans, inv[n - 1])), 0;
}