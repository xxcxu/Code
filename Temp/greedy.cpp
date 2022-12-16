#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
template<typename DataType>
inline DataType read() {
    DataType t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}
typedef long long ll;
const int N = 1e3 + 5, M = 5e5 + 5;
int n, S, q[M];
ll m, sum, ans;
ll A[2 * N], *a = A + N;
ll B[2 * N], *b = B + N;
ll f[M], g[M];
inline void replace(int x, int p, ll cnt) {
    if (x > 0) {
        for (int j = 0; j < x; ++j) {
            int l = 1, r = 0;
            for (int k = j; k <= (S << 1); k += x) {
                if (f[k] >= 0) {
                    g[k] = f[k] - p * (k / x);
                    while (l <= r && g[q[r]] < g[k]) -- r;
                    q[++ r] = k;
                }
                while (l <= r && q[l] < k - cnt * x) ++ l;
                f[k] = l <= r ? g[q[l]] + p * (k / x) : -1;
            }
        }
    } else if (x < 0) {
        for (int j = 0; j < -x; ++j) {
            int l = 1, r = 0;
            for (int k = (S << 1) - j; k >= 0; k += x) {
                if (f[k] >= 0) {
                    g[k] = f[k] - p * (k / x);
                    while (l <= r && g[q[r]] < g[k]) -- r;
                    q[++ r] = k;
                }
                while (l <= r && q[l] > k - cnt * x) ++ l;
                f[k] = l <= r ? g[q[l]] + p * (k / x) : -1;
            }
        }
    }
}
signed main() {
    freopen("greedy.in", "r", stdin);
    freopen("greedy.out", "w", stdout);
    n = read<int>(), m = read<ll>();
    for (int i = -n; i <= n; ++i) a[i] = read<ll>();
    for (int i = -n; i <= n; ++i) sum += i * a[i];
    if (m > sum) m = -m, std::reverse(a - n, a + n + 1);
    S = 2 * n * n, sum = 0;
    for (int i = -n; i <= 0; ++i) {
        b[i] = a[i];
        sum += i * b[i], ans += b[i];
    }
    if (m < sum) return puts("impossible"), 0;
    for (int i = 1; i <= n; ++i) {
        b[i] = std::min(a[i], (m - sum) / i);
        sum += i * b[i], ans += b[i];
    }
    std::memset(f, -1, sizeof f);
    f[S] = ans;
    for (int i = -n; i <= n; ++i) {
        replace(-i, -1, b[i]);
        replace(i, 1, a[i] - b[i]);
    }
    ll answer = f[S + (m - sum)];
    if (answer < 0) return puts("impossible"), 0;
    printf("%lld\n", answer);
    return 0;
}