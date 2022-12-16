#include <bits/stdc++.h>
const int N = 2e5 + 5;
int n, m, q, cnt, timestamp;
int dep[N], rt[N], l[N], r[N], f[N][25], g[N][25];
std::vector<int> G[N], bus[N];

struct treenode {
    int ls, rs, s;
} tr[N << 6];

void Dfs(int x) { // DFS求以x为根的子树在树上的DFS序左右端点 
    l[x] = ++ timestamp; // 一个空 
    dep[x] = dep[f[x][0]] + 1;
    for (int y : G[x]) // 枚举儿子 
        Dfs(y);
    r[x] = timestamp;
}

int Lca(int x, int y) { // 倍增求LCA 
    if (dep[x] < dep[y]) std::swap(x, y); // 钦定x为深度深的那一个 
    for (int i = 24; i >= 0; --i) // 将二者倍增跳到同一高度 
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    if (x == y) // 如果两点在同一位置 该位置即为LCA 直接返回 
        return x;
    for (int i = 24; i >= 0; --i) // 如果两者不同则一直往上跳 
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    return f[x][0]; // 最后的LCA一定为二者的父亲 
}

void Update(int &rt, int l, int r, int x) {
    tr[++ cnt] = tr[rt]; // 创建新的节点 
    ++ tr[cnt].s;
    rt = cnt;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        Update(tr[rt].ls, l, mid, x);
    else
        Update(tr[rt].rs, mid + 1, r, x); 
}

int Query(int rt, int l, int r, int ql, int qr) {
    if (!rt) return 0; // 如果该节点为空 则贡献为0 
    if (l == ql && r == qr) // 一个空 
		return tr[rt].s; 
    int mid = (l + r) >> 1;
    if (qr <= mid)
		return Query(tr[rt].ls, l, mid, ql, qr);
    else if (ql > mid)
		return Query(tr[rt].rs, mid + 1, r, ql, qr);
    else 
		return Query(tr[rt].ls, l, mid, ql, mid) + Query(tr[rt].rs, mid + 1, r, mid + 1, qr);
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) { // 读入存图 这里保证每个节点的父亲编号小于该节点 
        scanf("%d", &f[i][0]);
        G[f[i][0]].push_back(i);
    }
    for (int j = 1; j < 25; ++j) // 倍增求LCA 
        for (int i = 1; i <= n; ++i)
            f[i][j] = f[f[i][j - 1]][j - 1];
    Dfs(1);
    scanf("%d", &m);
    for (int i = 1; i <= n; ++i) g[i][0] = i; // g[i][j]表示当前节点往上走2^j条链能走到最浅的节点 
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        int lca = Lca(x, y);
        g[x][0] = std::min(g[x][0], lca);
        g[y][0] = std::min(g[y][0], lca);
        bus[l[x]].push_back(l[y]);
        bus[l[y]].push_back(l[x]);
    }
    for (int i = n; i >= 1; --i) // 一个空 
        g[f[i][0]][0] = std::min(g[f[i][0]][0], g[i][0]);
    for (int j = 1; j < 25; ++j)
        for (int i = 1; i <= n; ++i)
            g[i][j] = g[g[i][j - 1]][j - 1]; // 一个空 
    for (int i = 1; i <= n; ++i) {
        rt[i] = rt[i - 1];
        for (int j : bus[i])
            Update(rt[i], 1, n, j);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x == y) {
            puts("0");
            continue;
        }
        int lca = Lca(x, y);
        if (g[x][24] > lca || g[y][24] > lca) {
            puts("-1");
            continue;
        }
        int ans = 2; // 一个空 
        for (int j = 24; j >= 0; --j)
            if (g[x][j] > lca) {
                x = g[x][j];
                ans += 1 << j;
            }
        for (int j = 24; j >= 0; --j)
            if (g[y][j] > lca) {
                y = g[y][j];
                ans += 1 << j;
            }
        if (lca == x || lca == y)
            -- ans;
        else
            ans -= (bool)(Query(rt[r[x]], 1, n, l[y], r[y]) - Query(rt[l[x] - 1], 1, n, l[y], r[y]));
        printf("%d\n", ans);
    }
    return 0;
}
