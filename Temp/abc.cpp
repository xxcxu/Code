#include <bits/stdc++.h>
static constexpr int N = 1e3 + 5;
int n, m;
char s[N], t[N];
std::string S, T;
void solve() {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; ++i) if (s[i] == 'B') cnt1 ^= 1;
    for (int i = 1; i <= m; ++i) if (t[i] == 'B') cnt2 ^= 1;
    if (cnt1 != cnt2) return puts("NO"), void();
    S = "", T = "";
    for (int i = 1; i <= n; ++i) if (s[i] != 'B') S += s[i];
    for (int i = 1; i <= m; ++i) if (t[i] != 'B') T += t[i];

    for (bool FIND = 0; !FIND && (FIND = 1);) {
        size_t sa, sc, ta, tc;
        sa = S.find("AA"), sc = S.find("CC");
        ta = T.find("AA"), tc = T.find("CC");
        if (sa != S.npos) FIND = 0, S.erase(sa, 2);
        else if (sc != S.npos) FIND = 0, S.erase(sc, 2);
        if (ta != T.npos) FIND = 0, T.erase(ta, 2);
        else if (tc != T.npos) FIND = 0, T.erase(tc, 2);
    }

    if (S == T) return puts("YES"), void();
    else return puts("NO"), void();
}
signed main() {
    // freopen("abc.in", "r", stdin);
    // freopen("abc.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
}