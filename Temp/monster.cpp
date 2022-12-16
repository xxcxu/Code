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
static constexpr int N = 1e5 + 5, K = 25, inf = 0x3f3f3f3f;
int n, m, k, sum, ans;
int a[N], b[N], p[N];
bool check(int x) {
    int cnt = 1, ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += a[i];
        if (ans > x) ans = a[i], ++ cnt;
        if (a[i] > x) return false;
        if (cnt > k) return false;
    } return true;
}
signed main() {
    freopen("monster.in", "r", stdin);
    freopen("monster.out", "w", stdout);
    read(n, m, k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    for (int i = 1; i <= n; ++i) sum += a[i];
    for (int i = 0; i < m; ++i) p[i + 1] = i;
    std::random_shuffle(p + 1, p + m + 1); ans = sum + 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) a[j] = (b[j] + p[i]) % m;
        int l = 1, r = ans - 1;
        if (!check(r)) continue;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid + 1;
        } ans = std::min(ans, r);
    } return printf("%d\n", ans), 0;
}