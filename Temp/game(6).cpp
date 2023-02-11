#include <bits/stdc++.h>
#define eb emplace_back
static const int N = 1e5 + 5;
int n, in[N];
std::vector<int> e[N];
bool chain() {
    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 1) ++ cnt1;
        if (in[i] == 2) ++ cnt2;       
    }
    return (cnt1 == 2) && (cnt2 == n - 2);
}
bool fork() {
    for (int i = 1; i <= n; ++i) if (in[i] >= 3) {
        int cnt = 0;
        for (int j : e[i]) if (in[j] == 1) ++ cnt;
        if (cnt >= 2) return true;
    }
    return false;
}
void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) in[i] = 0;
    for (int i = 1; i <= n; ++i) e[i].clear();
    for (int i = 1; i <  n; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        e[u].eb(v); e[v].eb(u);
        ++ in[u]; ++ in[v];
    }
    if (chain()) puts(n & 1 ? "shudedaoli" : "amiyu");
    else puts(fork() ? "shudedaoli" : "amiyu");
}
signed main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0; 
}