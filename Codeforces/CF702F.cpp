#include <bits/stdc++.h>
static constexpr int N = 2e5 + 5;
int n, m, ans[N];
class shirt {
    public: int c, p;
    public: shirt(int c = 0, int p = 0):
        c(c), p(p) {}
    public: bool operator < (const shirt &a) {
        return p == a.p ? c < a.c : p > a.p;
    }
} a[N];
std::mt19937 builder(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> random_x(0, 32767);
class Node {
    public:
        int w, val, rand, tag1, tag2, id;
        Node *ls, *rs;
    public:
        Node(int w, int id):
            w(w), id(id), val(0) {
                rand = random_x(builder);
                ls = rs = nullptr;
                tag1 = tag2 = 0;
            }
        auto Pushdown() -> void {
            if (tag1) {
                ls ? ls -> tag1 += tag1, ls -> w -= tag1 : 0;
                rs ? rs -> tag1 += tag1, rs -> w -= tag1 : 0;
                tag1 = 0;
            }
            if (tag2) {
                ls ? ls -> tag2 += tag2, ls -> val += tag2 : 0;
                rs ? rs -> tag2 += tag2, rs -> val += tag2 : 0;
                tag2 = 0;
            }
        }
};
auto Split(Node *rt, int w, Node *&l, Node *&r) -> void {
    if (!rt) return (void)(l = 0, r = 0);
    rt -> Pushdown();
    if (rt -> w <= w) {
        Split(rt -> rs, w, l, r);
        rt -> rs = l;
        l = rt;
    }
    else {
        Split(rt -> ls, w, l, r);
        rt -> ls = r;
        r = rt;
    }
}
auto Merge(Node *a, Node *b) -> Node* {
    if (!a || !b) return a ? a : b;
    a -> Pushdown();
    b -> Pushdown();
    if (a -> rand < b -> rand) {
        a -> rs = Merge(a -> rs, b);
        return a;
    } else {
        b -> ls = Merge(a, b -> ls);
        return b;
    }
}
auto Insert(Node *&rt, Node *node) -> void {
    Node *a, *b;
    Split(rt, node -> w, a, b);
    rt = Merge(Merge(a, node), b);
}
auto Build(Node *rt, Node *&insert, int c) -> void {
    if (!rt) return;
    rt -> Pushdown();
    Build(rt -> ls, insert, c);
    Build(rt -> rs, insert, c);
    rt -> ls = rt -> rs = 0;
    Insert(insert, rt);
}
auto Ask(Node *rt) -> void {
    if (!rt) return;
    rt -> Pushdown();
    ans[rt -> id] = rt -> val;
    Ask(rt -> ls);
    Ask(rt -> rs);
}
auto Putag(Node *rt, int c, bool tag2) -> void {
    if (rt) {
        if (tag2) rt -> tag2 += c, rt -> val += c;
        else rt -> tag1 += c, rt -> w -= c;
    }
}
Node *rt;
auto main() -> decltype(0) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].c, &a[i].p);
    std::sort(a + 1, a + n + 1);
    scanf("%d", &m);
    for (int i = 1, v; i <= m; ++i) {
        scanf("%d", &v);
        Node *p = new Node(v, i);
        Insert(rt, p);
    }
    for (int i = 1, c; i <= n; ++i) {
        c = a[i].c;
        Node *a, *b, *d, *e;
        Split(rt, c - 1, a, b);
        Split(b, c * 2 - 1, d, e);
        b = d; d = e; e = nullptr;
        Putag(b, c, 0);
        Putag(b, 1, 1);
        Putag(d, c, 0);
        Putag(d, 1, 1);
        Build(b, a, c);
        rt = Merge(a, d);
    }
    Ask(rt);
    for (int i = 1; i <= m; ++i) printf("%d ", ans[i]);
    puts("");
    return 0;
}