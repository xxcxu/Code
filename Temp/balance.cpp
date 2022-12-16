#include <bits/stdc++.h>
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
static constexpr int N = 3e5 + 5;
int n, root;
bool flag1, flag2;
int mx[N], mx2[N], son[N], ans[N], size[N];
std::vector<int> e[N];
void dfs1(int x, int fa) {
    size[x] = 1;
    for (int y : e[x]) if (y != fa) {
        dfs1(y, x);
        size[x] += size[y];
        if (size[y] > mx[x]) mx[x] = size[y], son[x] = y;
    }
    if (n - size[x] > mx[x]) mx[x] = n - size[x], son[x] = fa;
}
void dfs2(int x, int fa, int P) {
    size[x] = 1, mx2[x] = 0;
    for (int y : e[x]) if (y != fa) {
        dfs2(y, x, P);
        size[x] += size[y];
        mx2[x] = std::max(mx2[x], size[y]);
    }
    mx2[x] = std::max(mx2[x], P - size[x]);
    if (!root || mx2[x] < mx2[root]) root = x;
}
void solve1() {
    for (int i = 1; i <= n; ++i) {
        if (i - 1 > n - i) printf("%d\n", i / 2);
        else printf("%d\n", (n + i + 1) / 2);
    }
}
void solve2() {
    printf("%d\n", 2);
    for (int i = 2; i <= n; ++i) printf("%d\n", 1);
}
signed main() {
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    read(n);
    flag1 = flag2 = true;
    for (int i = 1; i < n; ++i) {
        static int u, v;
        read(u, v);
        flag1 &= (u == i && v == i + 1);
        flag2 &= (u == 1 && v == i + 1);
        #define eb emplace_back
        e[u].eb(v); e[v].eb(u);
        #undef eb
    }
    if (flag1) return solve1(), 0;
    else if (flag2) return solve2(), 0;
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i) {
        ewroot = 0;
        dfs2(son[i], i, mx[i]);
        printf("%d\n", root);
    } return 0;
}
/*
10
1 2
2 4
2 9
9 3
9 8
3 7
3 10
7 6
6 5
*/