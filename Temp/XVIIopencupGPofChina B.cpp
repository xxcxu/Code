# include <bits/stdc++.h>

int read() {
    int t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}

int n, m, c[N];
std::vector<int> e[N];
bool flag = false;

void dfs(int x, int c) {
    for (int y : e[x]) {
        if (col[y]) {flag = col[y] == c;}
        else dfs(y, c ^ 1);
    }
}

signed main() {
    n = read(), m = read();
    for (int i = 1; i <= m; ++i) {
        static int u, v;
        u = read(), v = read();
        e[u].eb(v); e[v].eb(u);
    }
    dfs(1, 0);
    puts(flag ? "0" : "1");
    return 0;
}