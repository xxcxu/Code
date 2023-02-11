#include <bits/stdc++.h>
#define eb emplace_back
static const int N = 2005;
int n, m;
std::vector<int> a[N], b[N], c, d;
int next(int x) {return x == n ? 1 : x + 1;}
bool check(int a1, int a2, int a3) {
    for (int i : b[a1]) for (int j : b[a2]){
        if (i != j) return true;
        for (int k : b[a3]) if (k != i) return true; 
    }
    return false;
}
void subtask1() {
    static int p[N];
    std::iota(p + 1, p + n + 1, 1);
    do {
        bool flag = true;
        for (int i = 1; i <= n; ++i) if (!check(p[i], p[next(i)], p[next(next(i))])) flag = false;
        if (flag) {for (int i = 1; i <= n; ++i) printf("%d%c", p[i], " \n"[i == n]); return void();} 
    } while (std::next_permutation(p + 1, p + n + 1));
    return puts("-1"), void();
}
void subtask2() {
    c.clear(); d.clear();
    int size = a[1].size();
    int empty = n - size;
    if (n < 3) {for (int i = 1; i <= n; ++i) printf("%d%c", i, " \n"[i == n]); return void();}
    if (empty >= size / 2) {
        for (int i = 1; i <= n; ++i) (b[i].size() ? c : d).eb(i);
        int i = 0, j = 0;
        while (i <= size || j <= empty) {
            if (i + 1 <= empty) printf("%d ", c[++ i]);
            if (i + 1 <= empty) printf("%d ", c[++ i]);
            if (j + 1 <=  size) printf("%d ", d[++ j]);
        } puts("");
        return void();
    }
    return puts("-1"), void();
}
void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) a[i].clear();
    for (int i = 1; i <= n; ++i) b[i].clear();
    for (int i = 1; i <= m; ++i) {
        static int size;
        scanf("%d", &size);
        a[i].resize(size + 1);
        for (int j = 1; j <= size; ++j) scanf("%d", &a[i][j]);
        for (int j = 1; j <= size; ++j) b[a[i][j]].eb(i);
    }
    if (n <= 9) return subtask1();
    if (m == 1) return subtask2();
    return puts("-1"), void();
}
signed main() {
    freopen("contest.in", "r", stdin);
    freopen("contest.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}