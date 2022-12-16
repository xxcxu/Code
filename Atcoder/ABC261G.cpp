#include <bits/stdc++.h>
static constexpr int N = 55, inf = 1e9 + 7;
int n, m, k, ans;
int c[N], g[N], f[27][N][N];
std::string s, t;
std::string a[N];
bool flag; char ch;
signed main() {
    std::cin >> s >> t;
    scanf("%d", &k);
    n = (int)s.size(), m = (int)t.size();
	for (int i = 1; i <= k; ++i) {
        static char ch;
        std::cin >> ch >> a[i];
        c[i] = ch - 'a';
    }
    c[++ k] = 26; a[k] = s;
    std::memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= m; ++i)
        f[t[i - 1] - 'a'][i][i] = 0;
    for (int l = m; l >= 1; --l) {
        do {
            flag = false;
            for (int i = 1; i <= k; ++i) {
                std::memset(g, 0x3f, sizeof g);
                g[l - 1] = 0;
                for (auto ch : a[i])
                    for (int R = m; R >= l - 1; --R) {  // R [l - 1, m]
                        g[R] = inf;
                        for (int L = l - 1; L <= R - 1; ++L)
                            g[R] = std::min(g[R], g[L] + f[ch - 'a'][L + 1][R]);
                    }
                for (int r = l; r <= m; ++r)
                    if (f[c[i]][l][r] > g[r] + 1)
                        f[c[i]][l][r] = g[r] + 1, flag = true;
            }
        } while(flag);
    }
    ans = f[26][1][m] - 1;
    if (ans >= inf) ans = -1;
    printf("%d\n", ans);
	return 0;
}