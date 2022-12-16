// 命里有时终须有，命里无时莫强求
#include <bits/stdc++.h>
#define eb emplace_back
using pii = std::pair<int, int>;
static constexpr int N = 1e6 + 5;
int n, m, c[N], ans[N];
struct node {
    int x, y, id;
    node(int x = 0, int y = 0, int id = 0): x(x), y(y), id(id) {}
} a[N], q[N];
void add(int x) {for (; x <= n; x += x & -x) ++ c[x];}
int ask(int x) {int ans = 0; for (; x; x -= x & -x) ans += c[x]; return ans;}
signed main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        a[i] = node(std::min({u, v, i}), std::max({u, v, i}), i);
    }
    for (int i = 1; i <= m; ++i) {
        static int l, r;
        scanf("%d%d", &l, &r);
        q[i] = node(l, r, i);
        ans[i] = r - l + 1;
    }
    std::sort(a + 1, a + n, [](const node&a, const node&b) {return a.x > b.x;});
    std::sort(q + 1, q + m + 1, [](const node&a, const node&b) {return a.x > b.x;});
    for (int i = n, j = 1, k = 1; i >= 1; --i) {
        while (j < n && a[j].x == i) add(a[j].y), ++j;
        while (k <= m && q[k].x == i) ans[q[k].id] -= ask(q[k].y), ++k;
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    return 0;
}