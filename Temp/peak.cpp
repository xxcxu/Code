#include <bits/stdc++.h>
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
#define int long long
static constexpr int N = 2e5 + 5, inf = 1e18 + 7;
int n, m, k, p, now = 0, ans = inf;
int h[N], H[N], g[N];
class TreeArray {
    private: int s[N];
    public: void insert(int x) {for (; x <= n; x += x & -x) ++ s[x];}
    public: void erase(int x) {for (; x <= n; x += x & -x) -- s[x];}
    public: int ask(int x) {int ans = 0; for (; x; x -= x & -x) ans += s[x]; return ans;}
} tr1, tr2;
signed main() {
    freopen("peak.in", "r", stdin);
    freopen("peak.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; ++i) read(h[i]);
    for (int i = 1; i <= n; ++i) H[i] = h[i];
    std::sort(H + 1, H + n + 1); m = std::unique(H + 1, H + n + 1) - H - 1;
    for (int i = 1; i <= n; ++i) h[i] = std::lower_bound(H + 1, H + m + 1, h[i]) - H;

    for (int i = 1; i <= n; ++i) if (h[i] > h[p]) p = i;
    for (int i = 1; i <= n; ++i) if (i != p) g[++ k] = h[i];

    for (int i = 1; i <= k; ++i) tr2.insert(g[i]), now += tr2.ask(g[i] - 1);
    for (int i = 0; i <= k; ++i) {
        ans = std::min(ans, now + std::abs(p - i - 1));
        if (i == k) break;
        tr1.insert(g[i + 1]), now += (i + 1) - tr1.ask(g[i + 1] - 1) - 1;
        tr2.erase(g[i + 1]), now -= k - (i + 1) - tr2.ask(g[i + 1] - 1);
    }
    return printf("%lld\n", ans), 0;
}