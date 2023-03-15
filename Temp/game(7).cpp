#include <bits/stdc++.h>
using PII = std::pair<int, int>;

#define eb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()

static const int N = 200'005, inf = 0x3f3f3f3f;
int n, q, pos[N];
int dep[N], anc[N][32];
int d[N][3], d2[N][3], ans[N][3];
std::vector<int> e[N];
FILE* fin, * fout, * ferr;

struct Issue {
    int a, b, c, id;
    Issue(int a = 0, int b = 0, int c = 0, int id = 0): a(a), b(b), c(c), id(id) {}
};
std::vector<Issue> vec;
std::vector<int> ask[N];

struct TreeArray {
    PII s[N];
    void add(int x, PII t) {
        for (; x <= n; x += x & -x)
            s[x] = std::max(s[x], t);
        return void();
    }
    int ask(int x) {
        PII ans = PII(-1, -inf);
        for (; x; x -= x & -x) ans = std::max(ans, s[x]);
        return ans.se;
    }
} t;

PII add(PII b) { return !~b.fi ? b : PII(b.fi, b.se + 1); }

struct Node {
    PII a[3];
    Node() { a[0] = a[1] = a[2] = PII(-1, -inf); }
    void insert(PII b) {
        int p = 3;
        for (int i = 0; i < 3; ++i)
            if (a[i] < b) { p = i; break; }
        for (int i = 2; i > p; --i)
            a[i] = a[i - 1];
        if (p < 3) a[p] = b;
        return void();
    }
    PII& operator[](const int x) { return a[x]; }
    PII get(PII x) {
        for (int i = 0; i < 3; ++i)
            if (a[i] != x) return a[i];
        assert(0);
        return PII(-1, -inf);
    }
};

Node f[N], g[N];

int lca(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = 25; i >= 0;--i)
        if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (int i = 25; i >= 0; --i)
        if (anc[x][i] != anc[y][i])
            x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}

int jump(int x, int d) {
    for (int i = 25; i >= 0; --i)
        if (d >= (1 << i))
            d -= 1 << i, x = anc[x][i];
    return x;
}

int knode(int x, int y, int d) {
    int L = lca(x, y);
    if (dep[x] - dep[L] >= d)
        return jump(x, d);
    return jump(y, dep[x] + dep[y] - 2 * dep[L] - d);
}

void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    anc[x][0] = fa;
    for (int i = 1; i <= 25; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (int y : e[x])
        if (y != fa) {
            dfs(y, x);
            f[x].insert(add(f[y][0]));
        }
    for (int i = 0; i < 3; ++i)
        f[x].insert(PII(0, x));
    return void();
}

void dfs2(int x, int fa) {
    vec.eb(g[x].a[0].fi, g[x].a[1].fi, g[x].a[2].fi, x + q);
    for (int y : e[x])
        if (y != fa) {
            g[y] = f[y];
            g[y].insert(add(g[x].get(add(g[x][0]))));
            dfs2(y, x);
        }
    return void();
}

void dfs3(int x, int fa) {
    for (int id : ask[x]) {
        ans[id][0] = knode(x, g[x].a[0].se, d[id][0]);
        ans[id][0] = knode(x, g[x].a[1].se, d[id][1]);
        ans[id][0] = knode(x, g[x].a[2].se, d[id][2]);
    }
    for (int y : e[x])
        if (y != fa)
            dfs3(y, x);
    return void();
}

void solve() {
    std::sort(all(vec), [&](const Issue& a, const Issue& b) {
        return std::tie(a.a, a.b, a.c, a.id) < std::tie(b.a, b.b, b.c, b.id);});
    for (auto [a, b, c, id] : vec) {
        if (id > q) t.add(b, PII(c, id - q));
        else pos[id] = t.ask(b);
    }
    return void();
}

int dis(int x, int y) { return dep[x] + dep[y] - 2 * dep[lca(x, y)]; }

void calc(int* ans, int* d) {
    do {
        bool flag = false;
        if (dis(ans[0], ans[1]) == d[0])
            if (dis(ans[0], ans[2]) == d[1])
                if (dis(ans[1], ans[2]) == d[2])
                    flag = true;
        if (flag) return void();
    }
    while (std::next_permutation(ans, ans + 2));
    assert(0);
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("input.in", "r"), fout = fopen("output.out", "w+"), ferr = fopen("debug.out", "w+");
    fscanf(fin, "%d", &n);
    for (int i = 1; i < n; ++i) {
        static int u, v;
        fscanf(fin, "%d%d", &u, &v);
        e[u].eb(v), e[v].eb(u);
    }
    fscanf(fin, "%d", &q);
    for (int i = 1; i <= q; ++i) {
        static int x, y, z;
        fscanf(fin, "%d%d%d", &x, &y, &z);
        d2[i][0] = d[i][0] = (x + y - z) / 2;
        d2[i][1] = d[i][1] = (x + z - y) / 2;
        d2[i][2] = d[i][2] = (y + z - x) / 2;
        std::sort(d[i], d[i] + 2);
        vec.eb(d2[i][0], d2[i][1], d2[i][2], i);
    }
    dfs(1, 0);
    g[1] = f[1];
    dfs2(1, 0);

    for (int i = 1; i <= n; ++i) {
        fprintf(ferr, "%d ", g[i].a[0].se);
        fprintf(ferr, "%d ", g[i].a[1].se);
        fprintf(ferr, "%d\n", g[i].a[2].se);
    }

    solve();
    for (int i = 1; i <= q; ++i) ask[pos[i]].eb(i);
    dfs3(1, 0);
    for (int i = 1; i <= q; ++i) {
        calc(ans[i], d2[i]);
        fprintf(fout, "%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
    }
    return 0;
}