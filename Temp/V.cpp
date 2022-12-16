#include <bits/stdc++.h>
static constexpr int N = 2e4 + 5;
char str[N], s1[N], s2[N];
bool check(char *str, int n) {
    int l = 0;
    for (int i = 1; i <= n; ++i) {
        if (str[i] == '(') ++ l;
        else if (str[i] == ')') -- l;
        if (l < 0) return false;
    }
    if (l > 0) return false;
    return true;
}
void solve() {
    scanf("%s", str + 1);
    int n = strlen(str + 1);
    int L = 0, R = 0;
    for (int i = 1; i <= n; ++i) {
        if (str[i] == '(') ++ L;
        else ++ R;
    }
    if (L != R) return puts("No"), void();
    int m = 0, k = 0, l = 0, r = 0;
    for (int i = 1; i <= n; ++i) {
        if (str[i] == '(') {
            ++ l;
            if (l >= 1 && l <= n / 4) s1[++ m] = '(';
            else s2[++ k] = '(';
        }
        if (str[i] == ')') {
            ++ r;
            if (n / 4 < r && r <= n / 2) s1[++ m] = ')';
            else s2[++ k] = ')';
        }
    }
    for (int i = 1; i <= m; ++i) s2[i] = (s2[i] == '(' ? ')' : '(');
    if (m == k && check(s1, m) && check(s2, k)) return puts("Yes"), void();
    else return puts("No"), void();
}
signed main() {
    freopen("V.in", "r", stdin);
    freopen("V.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}   