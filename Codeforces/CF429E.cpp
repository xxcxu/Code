# include <bits/stdc++.h>

#define eb emplace_back

using pii = std::pair<int, int>;

int read() {
    int t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}

static const int N = 600005;

int n, m, l[N], r[N];
int c[N], d[N], col[N], vis[N];

int E = 1, to[N], nxt[N], hd[N];

void add(int x, int y) {
    ++ E;
    to[E] = y;
    nxt[E] = hd[x];
    hd[x] = E;
}

void dfs(int x) {
    vis[x] = true;
    for (int i = hd[x]; i; i = nxt[i]) {
        if (!~col[i >> 1]) {
            col[i >> 1] = i & 1;
            dfs(to[i]);
        }
    }
}

signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", l + i, r + i);
        ++ r[i];
        c[++ m] = l[i];
        c[++ m] = r[i];
    }
    std::sort(c + 1, c + m + 1);
    m = std::unique(c + 1, c + m + 1) - c - 1;
    for (int i = 1; i <= n; ++i) {
        l[i] = std::lower_bound(c + 1, c + m + 1, l[i]) - c;
        r[i] = std::lower_bound(c + 1, c + m + 1, r[i]) - c;
        ++ d[l[i]]; -- d[r[i]];
        add(l[i], r[i]);
        add(r[i], l[i]);
    }
    for (int i = 1; i <= m; ++i) {
        d[i] += d[i - 1];
        if (d[i] & 1) 
            add(i, i + 1), add(i + 1, i);
    }
    std::memset(col, -1, sizeof col);
    for (int i = 1; i <= m; ++i) if (!vis[i]) dfs(i);
    for (int i = 1; i <= n; ++i) printf("%d ", col[i]);
    return 0;
}