#include <bits/stdc++.h>
#define int long long
static const int N = 20;
int n, m, f[N], pow_10[N], cnt[2][N];
void solve(int x, int *a) {
    static int p[N];
    int k = 0;
    while (x) p[++ k] = x % 10, x /= 10;
    for (int i = k; i > 0; --i) {
        for (int j = 0; j <= 9; ++j) a[j] += f[i - 1] * p[i];
        for (int j = 0; j < p[i]; ++j) a[j] += pow_10[i - 1];
        int res = 0;
        for (int j = i - 1; j >= 1; --j) res = res * 10 + p[j];
        a[p[i]] += res + 1;
        a[0] -= pow_10[i - 1];
    } return void();
}
signed main() {
    scanf("%lld%lld", &n, &m);
    pow_10[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = f[i - 1] * 10 + pow_10[i - 1];
        pow_10[i] = pow_10[i - 1] * 10;
    }
    solve(n - 1, cnt[0]);
    solve(m    , cnt[1]);
    for (int i = 0; i <= 9; ++i) printf("%lld ", cnt[1][i] - cnt[0][i]);
    puts("");
    return 0;
}