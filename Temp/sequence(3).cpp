#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5;
int n, m, f[N];
char s[N], t[N];
std::vector<int> begin, end;
signed main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    int p = 1, p2 = 0;
    f[n + 1] = m + 1;
    for (int i = n; i >= 1; --i) {
        f[i] = f[i + 1];
        if (s[i] == t[f[i] - 1]) -- f[i];
        if (f[i] == 1) {p = i; break;}
    }
    for (int i = 1, j = 1; i <= n + 1; ++i) {
        if (i >= p && f[i] == j) {p2 = i; break;}
        if (s[i] == s[i + 1] || i >= n) continue;
        if (j > m) return puts("NO"), 0;
        if (t[j] == s[i]) begin.emplace_back(i);
        if (t[j] == s[i + 1]) begin.emplace_back(++ i);
        ++ j;
    }
    if (!p2) return puts("NO"), 0;
    int j = m;
    for (int i = n; i >= p2; --i) if (s[i] == t[j]) end.emplace_back(i), -- j;
    std::reverse(end.begin(), end.end());
    puts("YES");
    for (int i : begin) printf("%d ", i);
    for (int i : end) printf("%d ", i);
    puts("");
    return 0;
}