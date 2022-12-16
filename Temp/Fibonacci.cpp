#include <bits/stdc++.h>
static constexpr int N = 3e3 + 5;
int n, m, a[N], dp[N][N];
std::unordered_map<int, int> map;
void cmin(int &x, int y) {if (y < x) x = y;}
void cmax(int &x, int y) {if (y > x) x = y;}
signed main() {
    freopen("fibonacci.in", "r", stdin);
    freopen("fibonacci.out", "w", stdout);
    scanf("%d", &n); 
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) dp[0][i] = 1;
    map[a[1]] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) dp[i][j] = 2;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int p = a[j] - a[i];
            if (map.count(p)) cmax(dp[i][j], dp[map[p]][i] + 1);
        }
        map[a[i]] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            cmax(ans, dp[i][j]);
    return printf("%d\n", ans), 0;
}