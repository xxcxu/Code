#include <bits/stdc++.h>
static constexpr int N = 5e5 + 5, P = 998244353, inv2 = P + 1 >> 1;
int n, cnt = 1;                                             
int ch[N][26], tp[N], u[N], del[N], add[N], a[N];
std::string src[N];
auto inc(int x, int y) {x += y - P; return x + (x >> 31 & P);}
auto dec(int x, int y) {x -= y; return x + (x >> 31 & P);}
auto mul(int x, int y) {return 1ll * x * y % P;}
auto Insert(int p, int d, int x) {
    if (d == a[x] - 1) {
        ++ tp[p];
        return void();
    }
    ++ d;
    int c = src[x][d] - 'a';
    if (!ch[p][c]) ch[p][c] = ++ cnt;
    Insert(ch[p][c], d, x);
    ++ u[p];
}
auto Query(int p, int d, int x) {
    if (d == a[x] - 1) {
        del[x] = u[p];
        return void();
    }
    ++ d;
    int c = src[x][d] - 'a';
    add[x] += tp[p];
    Query(ch[p][c], d, x);
}
auto main() -> decltype(0) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        std::cin >> src[i];
        a[i] = (int)src[i].size();
        Insert(1, -1, i);
    }
    for (int i = 1; i <= n; ++i)
        Query(1, -1, i);
    for (int i = 1; i <= n; ++i) {
        int ans = add[i] + 1;
        int sum = (n - add[i] - del[i] - 1);
        ans = inc(ans, mul(sum, inv2));
        printf("%d\n", ans);
    }
    return 0;
}