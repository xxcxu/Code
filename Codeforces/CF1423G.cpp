#include <bits/stdc++.h>
#define int long long
static const int N = 200005;
int n, m, cnt;
std::map<int, int> map;
struct Node {
    int l, r, v;
    Node(int l = -1, int r = -1, int v = 0): l(l), r(r), v(v) {}
    bool operator < (const Node &a) const {return this -> l < a.l;}
};
class TreeArray {
    #define lowbit(x) ((x) & -(x))
    public:
        void add(int x, int v) {for (; x <= n; x += lowbit(x)) c[x] += v; return void();}
        int ask(int x) {int ans = 0; for (; x >= 1; x -= lowbit(x)) ans += c[x]; return ans;}
        int ask(int l, int r) {return ask(r) - ask(l - 1);}
    private:
        static const int V = N;
        int c[V];
} t0, t1;
using sit = std::set<Node>::iterator;
std::set<Node> set, s[N];
sit split(int p) {
    auto it = set.lower_bound(Node(p));
    if (it != set.end() && it -> l == p) return it;
    -- it; auto [l, r, v] = *(it);
    s[v].erase(Node(l, r, v)); set.erase(Node(l, r, v)); 
    s[v].insert(Node(l, p - 1, v)), s[v].insert(Node(p, r, v));
    set.insert(Node(l, p - 1, v));
    return set.insert(Node(p, r, v)).first;
}
void ins(Node a) {
    auto [l, r, v] = a;
    int next = (s[v].upper_bound(a)) -> l;
    int pre  = (-- s[v].lower_bound(a)) -> r;
    t0.add(next - pre - 1, -1); t1.add(next - pre - 1, pre - next + 1);
    if (pre + 1 != l) t0.add(l - pre - 1, 1), t1.add(l - pre - 1, l - pre - 1);
    if (next - 1 != r) t0.add(next - r - 1, 1), t1.add(next - r - 1, next - r - 1);
    s[v].insert(a);
}
void del(Node a) {
    auto [l, r, v] = a;
    int next = (s[v].upper_bound(a)) -> l;
    int pre  = (-- s[v].lower_bound(a)) -> r;
    t0.add(next - pre - 1, 1); t1.add(next - pre - 1, next - pre - 1);
    if (pre + 1 != l) t0.add(l - pre - 1, -1), t1.add(l - pre - 1, pre - l + 1);
    if (next - 1 != r) t0.add(next - r - 1, -1), t1.add(next - r - 1, r - next + 1);
    s[v].erase(a);
}
void assign(int l, int r, int v) {
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it) del(*it);
    set.erase(itl, itr);
    set.insert(Node(l, r, v));
    ins(Node(l, r, v));
}
int hash() {
    static int x;
    scanf("%lld", &x);
    if (!map[x]) map[x] = ++ cnt;
    return map[x];
}
signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i) s[i].insert(Node(-1, 0));
    for (int i = 1; i <= n; ++i) s[i].insert(Node(n + 1, n + 2));
    set.insert(Node(-1, 0, 0));
    set.insert(Node(n + 1, n + 2, 0));
    t0.add(n, n), t1.add(n, n * n);
    for (int i = 1; i <= n; ++i) {
        static int x;
        x = hash();
        ins(Node(i, i, x));
        set.insert(Node(i, i, x));
    }
    while (m--) {
        static int op, l, r, x;
        scanf("%lld", &op);
        if (op == 1) scanf("%lld%lld", &l, &r), x = hash(), assign(l, r, x);
        if (op == 2) scanf("%lld", &x), printf("%lld\n", n * (n + 1 - x) - t1.ask(x, n) + (x - 1) * t0.ask(x, n));
    }
    return 0;
}