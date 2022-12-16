#include <bits/stdc++.h>
constexpr int N = 1e6 + 5;
int n, m, p;
bool vis[N];
struct operat {int opt, x;} a[N], b[N];
void solve() {
    scanf("%d%d", &p, &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].opt, &a[i].x);
    for (int i = 1; i <= n; ++i) if (a[i].opt) b[++ m] = a[i];
    if (m <= 12) {
        int ans = p;
        for (int i = 0; i < p; ++i) vis[i] = false;
        for (int i = n - m + 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (a[i].opt) continue;
                int sta = (1 << (n - i));
                while (sta < 1 << m) {
                    int w = a[i].x;
                    for (int k = 1; k <= m; ++k) if (sta >> k & 1) w = 1ll * w * b[k].x % p; 
                    if (!vis[w]) -- ans, vis[w] = true;
                    int x = sta & -sta, y = sta + x;
                    sta = ((sta & ~y) / x >> 1) | y;
                }
            }
        }
        printf("%d\n", ans);
    }
}
signed main() {
    // freopen("zjiang.in", "r", stdin);
    // freopen("zjiang.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}