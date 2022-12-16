#include <bits/stdc++.h>
#define eb emplace_back
static constexpr int N = 5e3 + 5, P = 998244353;
int n, g[N], fa[N], fac[N], inv[N], size[N], dp[N][N];
std::vector<int> e[N];
bool leaf(int x) {return e[x].empty();}

int inc(int x, int y); int dec(int x, int y);
int mul(int x, int y); int qpow(int x, int y, int P);
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x)) if (y & 1) ans = mul(ans, x);
    return ans % P;
}
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1ll * x * y % P;}
int binom(int x, int y) {return x < y ? 0 : mul(fac[x], mul(inv[y], inv[x - y]));}

void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
    inv[n] = qpow(fac[n], P - 2, P);
    for (int i = n - 1; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % P;
    return void();
}

void dfs(int x, int pre) {
    if (leaf(x)) dp[x][0] = 1;
    for (int y : e[x]) if (y != pre) {
        dfs(y, x);
        if (!dp[x][0]) {
            for (int i = 0; i < size[y]; ++i) dp[x][i] = dp[y][i];
            size[x] += size[y];
            continue;
        }
        for (int i = 0; i < size[x] + size[y]; ++i) g[i] = 0;
        for (int i = 0; i < size[x]; ++i)
            for (int j = 0; j < size[y]; ++j)
                g[i + j] = inc(g[i + j], mul(mul(dp[x][i], dp[y][j]), binom(size[x] + size[y] - i - j, size[y] - j))); 
        for (int i = 0; i < size[x] + size[y]; ++i) dp[x][i] = g[i];
        size[x] += size[y];
    }
    ++ size[x];
    for (int i = size[x] - 1; i >= 0; --i) {
        dp[x][i] = mul(dp[x][i], size[x] - i);
        if (i) dp[x][i] = inc(dp[x][i], mul(dp[x][i - 1], size[x] - i));
    }
}
signed main() {
    freopen("climb.in", "r", stdin);
    freopen("climb.out", "w", stdout);
    scanf("%d", &n); init(n);
    for (int i = 2; i <= n; ++i) scanf("%d", fa + i);
    for (int i = 2; i <= n; ++i) e[fa[i]].eb(i); 
    dfs(1, 0);
    for (int i = 0; i < n; ++i) {
        int res = 0;
        for (int j = i; j < n; ++j) {
            if ((j - i) & 1) res = dec(res, mul(binom(j, i), dp[1][j]));
            else res = inc(res, mul(binom(j, i), dp[1][j]));
        }
        printf("%d ", res);
    }
    return 0;
}