#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
template <typename T>
T read()
{
    T x = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar())
        x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? ~x + 1 : x;
}
const int N = 2e5 + 5;
int siz[N], fa[N][20], val[N][20], son[N], dfn[N], top[N], tot, cnt, n, dep[N], c[N], st[N], m, T, ff[N], q;
vector<int> E[N], G[N], pos[N];
ll t[N << 2], mx1[N], mx2[N], w[N], w1[N], w2[N];
struct nade
{
    int u, v, w;
    bool operator<(const nade &x)
    {
        return w < x.w;
    }
} e[N << 1];
void dfs(int u)
{
    siz[u] = 1;
    dep[u] = dep[fa[u][0]] + 1;
    for (int v : E[u])
    {
        fa[v][0] = u;
        dfs(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}
void dfs3(int u, int tp)
{
    top[u] = tp;
    dfn[u] = ++tot;
    if (son[u])
        dfs3(son[u], tp);
    for (int v : E[u])
        if (v ^ son[u])
            dfs3(v, v);
}
bool cmp(int x, int y) { return dfn[x] < dfn[y]; }
int LCA(int u, int v)
{
    while (top[u] ^ top[v])
        if (dep[top[u]] < dep[top[v]])
            v = fa[top[v]][0];
        else
            u = fa[top[u]][0];
    return dep[u] < dep[v] ? u : v;
}
void change(int x, int l, int r, int L, int R, ll w)
{
    if (l >= L && r <= R)
    {
        t[x] += w;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= L)
        change(x << 1, l, mid, L, R, w);
    if (mid + 1 <= R)
        change(x << 1 | 1, mid + 1, r, L, R, w);
}
ll ask(int x, int l, int r, int p)
{
    if (l == r)
        return t[x];
    int mid = (l + r) >> 1;
    if (mid >= p)
        return ask(x << 1, l, mid, p) + t[x];
    return ask(x << 1 | 1, mid + 1, r, p) + t[x];
}
void change(int u, int v, ll w)
{
    if (u == 0)
    {
        u = cnt;
        while (top[u] ^ top[v])
        {
            change(1, 1, cnt, dfn[top[v]], dfn[v], w);
            v = fa[top[v]][0];
        }
        change(1, 1, cnt, 1, dfn[v], w);
        return;
    }
    while (top[u] ^ top[v])
    {
        change(1, 1, cnt, dfn[top[v]], dfn[v], w);
        v = fa[top[v]][0];
    }
    if (u ^ v)
        change(1, 1, cnt, dfn[u] + 1, dfn[v], w);
}
void dfs1(int u, int col, int la)
{
    mx1[u] = (c[u] == col ? w1[u] : 0);
    mx2[u] = (c[u] == col ? w2[u] : 0);
    for (int v : G[u])
    {
        dfs1(v, col, u);
        mx1[u] = max(mx1[u], mx1[v]);
        mx2[u] = max(mx2[u], mx2[v]);
    }
    change(la, u, mx2[u] - mx1[u]);
    G[u].clear();
}
void add(int u, int v) { G[u].pb(v); }
void make(int i, int u, int v)
{
    int top;
    st[top = 1] = pos[i][0];
    for (int j = 1; j < pos[i].size(); j++)
    {
        int u = pos[i][j], lca = LCA(u, st[top]);
        while (1)
        {
            if (dep[lca] >= dep[st[top - 1]])
            {
                if (lca != st[top])
                {
                    add(lca, st[top]);
                    if (lca != st[top - 1])
                        st[top] = lca;
                    else
                        top--;
                }
                break;
            }
            else
            {
                add(st[top - 1], st[top]);
                top--;
            }
        }
        st[++top] = u;
    }
    while (--top)
        add(st[top], st[top + 1]);
    for (auto id : pos[i])
        w1[id] = (u ? w[id] : 0), w2[id] = w[id];
    w2[u] += v;
    dfs1(st[1], i, 0);
    w[u] += v;
}
int find(int x) { return ff[x] == x ? x : ff[x] = find(ff[x]); }
void init()
{
    memset(c, 0, sizeof c);
    memset(w, 0, sizeof w);
    memset(son, 0, sizeof son);
    memset(fa, 0, sizeof fa);
    memset(val, 0, sizeof val);
    for (int i = 1; i <= cnt; i++)
    {
        pos[i].clear();
        E[i].clear();
    }
    cnt = 0;
    tot = 0;
}
void build(int x, int l, int r)
{
    t[x] = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
}
signed main()
{
    // freopen("building.in","r",stdin);
    // freopen("building.out","w",stdout);
    T = read<int>();
    while (T--) {
        n = read<int>();
        m = read<int>();
        q = read<int>();
        for (int i = 1; i <= n; i++)
            c[i] = read<int>(), pos[c[i]].pb(i);
        for (int i = 1; i <= n; i++)
            w[i] = read<ll>();
        for (int i = 1; i <= m; i++)
            e[i].u = read<int>(), e[i].v = read<int>(), e[i].w = read<int>();
        sort(e + 1, e + m + 1);
        for (int i = 1; i <= n; i++)
            ff[i] = i;
        cnt = n;
        for (int i = 1; i <= m; i++)
            if (find(e[i].u) ^ find(e[i].v))
            {
                cnt++;
                int u = find(e[i].u), v = find(e[i].v);
                ff[u] = ff[v] = cnt;
                ff[cnt] = cnt;
                val[u][0] = val[v][0] = e[i].w;
                E[cnt].pb(u);
                E[cnt].pb(v);
            }
        build(1, 1, cnt);
        dfs(cnt);
        dfs3(cnt, cnt);
        for (int i = 1; i <= n; i++)
            sort(pos[i].begin(), pos[i].end(), cmp);
        for (int j = 1; j <= 19; j++)
            for (int i = 1; i <= cnt; i++)
            {
                fa[i][j] = fa[fa[i][j - 1]][j - 1];
                val[i][j] = max(val[fa[i][j - 1]][j - 1], val[i][j - 1]);
            }
        for (int i = 1; i <= n; i++)
            if (pos[i].size())
                make(i, 0, 0);
        while (q--)
        {
            int op, u, v;
            op = read<int>();
            u = read<int>();
            v = read<int>();
            if (op == 0)
            {
                make(c[u], u, v);
            }
            else
            {
                int x = u, w = v;
                for (int i = 19; i >= 0; i--)
                    if (val[x][i] <= w && fa[x][i])
                        x = fa[x][i];
                printf("%lld\n", ask(1, 1, cnt, dfn[x]));
            }
        }
        init();
    }
}