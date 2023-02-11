#include <bits/stdc++.h>
#define int long long
#define eb emplace_back
static const int N = 500000, N2 = N + 5;
int n, ans, tot, w[N2], rt[N2], dep[N2], val[N2];
std::vector<int> e[N2];
std::priority_queue<int, std::vector<int>, std::greater<int>> q;
class TreeArray {
    #define lowbit(x) ((x) & -(x))
    public:
        void add(int x, int v) {for (; x <= N; x += lowbit(x)) s[x] += v; return void();}
        int ask(int x) {int ans = 0; for (; x >= 1; x -= lowbit(x)) ans += s[x]; return ans;}
        int ask(int l, int r) {return l <= r ? ask(r) - ask(l - 1) : 0;}
    private:
        static const int V = N2;
        int s[V];
} bit;
class SegmentTree {
    public:
        void insert(int &x, int l, int r, int p) {
            tr[x = ++ tot] = 1;
            if (l == r) return void();
            int mid = (l + r) >> 1;
            p <= mid ? insert(ls[x], l, mid, p) : insert(rs[x], mid + 1, r, p);
            return void();
        }
        int query(int x, int l, int r, int ql, int qr) {
            if (!x) return 0;
            if (ql <= l && r <= qr) return tr[x];
            int mid = (l + r) >> 1, ans = 0;
            if (ql <= mid) ans += query(ls[x], l, mid, ql, qr);
            if (qr >  mid) ans += query(rs[x], mid + 1, r, ql, qr);
            return ans;
        }
        void merge(int &x, int y, int l, int r) {
            if (!x || !y) return x += y, void();
            if (l == r) return tr[x] += tr[y], void();
            int mid = (l + r) >> 1;
            merge(ls[x], ls[y], l, mid);
            merge(rs[x], rs[y], mid + 1, r);
            tr[x] = tr[ls[x]] + tr[rs[x]];
            return void();
        }
    private:
        static const int M = N2 * 69;
        int tr[M], ls[M], rs[M];
} seg;
int C2(int n) {return n * (n - 1) / 2;}
void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    val[x] = bit.ask(1, w[x]), bit.add(w[x], 1);
    ans += dep[x] - val[x] - 1;
    for (int y : e[x]) if (y != fa) {
        dfs(y, x);
        seg.merge(rt[x], rt[y], 1, N + 1);
    }
    bit.add(w[x], -1);
    val[x] += seg.query(rt[x], 1, N + 1, w[x] + 1, N + 1);
    return void();
}
signed main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", w + i);
    for (int i = 1; i < n; ++i) {
        static int u, v;
        scanf("%lld%lld", &u, &v);
        e[u].eb(v); e[v].eb(u);
    }
    for (int i = 1; i <= n; ++i) seg.insert(rt[i], 1, N + 1, w[i]);
    dfs(1, 0);
    printf("%lld ", C2(n) + ans);
    for (int i = 1; i <= n; ++i) q.emplace(val[i] - dep[i] + 1);
    for (int i = 1; i <= n; ++i) {
        ans += q.top(); q.pop();
        printf("%lld ", ans + C2(n - i));
    }
    return 0;
}