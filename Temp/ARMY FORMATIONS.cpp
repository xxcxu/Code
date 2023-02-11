#include <bits/stdc++.h>
#define int long long
#define eb emplace_back
static const int N = 100005;
int n, a[N], f[N], size[N], size2[N], ch[N][2];
std::vector<int> e[N];
class TreeArray {
    public:
        void add(int x, int v) {for (; x <= n; x += lowbit(x)) s[x] += v;}
        int ask(int x) {int ans = 0; for (; x >= 1; x -= lowbit(x)) ans += s[x]; return ans;}
    private:
        int lowbit(int x) {return x & (-x);}
        int s[N];
} t1, t2;
void init(int x, int fa) {
    for (int y : e[x]) if (y != fa) {
        init(y, x);
        ch[x][!!ch[x][0]] = y;
    } return void();
}
void dfs1(int x) {
    size2[x] = 1;
    if (ch[x][0]) dfs1(ch[x][0]), size2[x] += size2[ch[x][0]];
    if (ch[x][1]) dfs1(ch[x][1]), size2[x] += size2[ch[x][1]];
    return void();
}
void ins(int x, int &val, int &siz) {
    ++ siz;
    val += t1.ask(a[x]), t1.add(a[x], a[x]);
    val += 1ll * (siz - t2.ask(a[x])) * a[x], t2.add(a[x], 1ll);
    return void();
}
void del(int x) {t1.add(a[x], -a[x]); t2.add(a[x], -1ll);} 
void dfs2(int x, int y, int v) {
    if (v == 1)  ins(x, f[y], size[y]);
    if (v == -1) del(x), -- size[y];
    if (ch[x][0]) dfs2(ch[x][0], y, v);
    if (ch[x][1]) dfs2(ch[x][1], y, v);
} 
void dfs(int x) {
    if (!ch[x][0] && !ch[x][1]) return ins(x, f[x], size[x]);
    int s1 = size2[ch[x][0]], s2 = size2[ch[x][1]];
    if (s1 < s2) std::swap(ch[x][0], ch[x][1]);
    if (ch[x][1]) dfs(ch[x][1]);
    if (ch[x][1]) dfs2(ch[x][1], ch[x][1], -1);
    dfs(ch[x][0]), f[x] = f[ch[x][0]], size[x] = size[ch[x][0]];
    if (ch[x][1]) dfs2(ch[x][1], x, 1);
    ins(x, f[x], size[x]);
    return void();
}
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for (int i = 1; i <  n; ++i) {
        static int u, v;
        scanf("%lld%lld", &u, &v);
        e[u].eb(v); e[v].eb(u);
    } init(1, 0), dfs1(1), dfs(1);
    for (int i = 1; i <= n; ++i) printf("%lld%c", f[i], " \n"[i == n]);
    return 0;
}