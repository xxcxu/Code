#include <bits/stdc++.h>
#define int long long
const int N = 1e2 + 5;
int n, m, s, len, ans;
int a[N], f[N], fac[N], bel[N];
std::string str;
std::vector<int> v[N];
int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x *= x) if (y & 1) ans *= x;
    return ans;
}
void Judge() {
    int tmp[N], sl = (1ll << len) - 1, cnt = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            if (bel[i] == bel[j]) sl -= 1ll << cnt;
            ++ cnt;
        }
    int b[N] = {cnt = 0};
    for (int i = 1; i <= s; ++i) {
        tmp[i] = a[i] & sl;
        for (int j = len - 1; ~j; --j)
            if (1ll << j & tmp[i]) {
                if (!b[j]) {
                    ++ cnt;
                    b[j] = tmp[i];
                    break;
                }
                tmp[i] ^= b[j];
            }
    }
    ans += qpow(2, s - cnt) * f[m];
}
void Dfs(int x) {
    if (x > n) return void(Judge());
    v[++ m].emplace_back(x);
    bel[x] = m;
    Dfs(x + 1);
    v[m --].pop_back();
    for (int i = 1; i <= m; ++i) {
        bel[x] = i;
        v[i].emplace_back(x);
        Dfs(x + 1);
        v[i].pop_back();
    }
}
signed main() {
    std::cin >> s;
    for (int i = 1; i <= s; ++i) {
        std::cin >> str;
        std::reverse(str.begin(), str.end());
        len = str.size();
        for (int j = 0; j < len; ++j) a[i] = (a[i] << 1) | (str[j] ^ 48);
    }
    n = (std::sqrt(8 * len + 1) + 1) / 2;
    f[1] = fac[1] = 1;
    for (int i = 2; i <= n; ++i) {
        f[i] = f[i - 1] * (-1) * (i - 1);
        fac[i] = fac[i - 1] * i;
    }
    Dfs(1);
    return std::cout << ans, 0;
}