#include <bits/stdc++.h>
static constexpr int N = 9, M = 1e5 + 5;
int n, m, p[N];
int ch[M][27], size[M];
std::string str, s[N], t[M];
void insert(std::string s) {
    int p = 1;
    for (int i = 0; i < s.size(); ++i) {
        int c = s[i] == '-' ? 26 : s[i] - 'a';
        p = ch[p][c];
        ++ size[p];
    } return void();
}
int C(int n, int m) {
    int ans = 1;
    for (int i = n; i > n - m; ++i) ans = ans * i;
    for (int i = 1; i <= m; ++i) ans = ans / i;
    return ans;
}
int dfs(int x, int last) {
    int p = 1;
    for (int i = 0; i < s[x].size(); ++i)
        p = ch[p][s[x][i] - 'a'];
    int r = C(last - 1, n - x);
    if (size[ch[p][26]] >= r)
}
auto main() -> decltype(0) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) std::cin >> s[i];
    for (int i = 1; i <= m; ++i) std::cin >> t[i];
    for (int i = 1; i <= n; ++i) p[i] = i;
    for (int i = 1; i <= m; ++i) insert(t[i]);
    do {
        str = "";
        for (int i = 1; i <= n; ++i) str = str + s[p[i]];
        
    } while (std::next_permutation(p + 1, p + n + 1));
    return 0;
}