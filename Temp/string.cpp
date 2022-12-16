#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5;
int n, m, k, ans, f[N][30];
char s[N], t[N], p[N];
int calc() {
    for (int i = 1; i <= k; ++i)
        if (p[i] < s[i]) return m - k;
        else if (p[i] > s[i]) return N + 1;
    if (k != n) return m - k;
    return N + 1;                                                                                                                                                                                  
}
void dfs(int x) {
    if (x == m + 1) return ans = std::min(ans, calc()), void();
    p[++ k] = t[x];
    dfs(x + 1);
    -- k;
    dfs(x + 1);
}
void subtask2() {
    ans = m;
    dfs(1);
    printf("%d\n", ans);
}
signed main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    if (n <= 20 && m <= 20) return subtask2(), 0;
    for (int i = 0; i < 26; ++i) f[m + 1][i] = N + 1;
    for (int i = 0; i < 26; ++i)    
        for (int j = m; j >= 1; --j) {
            f[j][i] = f[j + 1][i];
            if (t[j] - 'a' < i) f[j][i] = j;
        }
    int res = 0; ans = n; 
    for (int i = 1, j = 1; i <= n && j <= m; ++i, ++j) {
        ans = std::min(ans, res + f[j][s[i] - 'a'] - j);
        while (t[j] > s[i]) ++ j, ++ res;
        if (t[j] < s[i]) {ans = std::min(ans, res); break;}
    }
    printf("%d\n", ans);
}