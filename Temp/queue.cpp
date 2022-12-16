#include <bits/stdc++.h>
using pii = std::pair<int, int>;
static constexpr int N = 4e5 + 5;
int n;
// 第i个点初值为i 
// 记录区间最大值
// 支持区间-1 
// 支持查找最左边的>=v的位置 
class SegmentTree { 
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    private: class TreeNode {public: int val, l, r, lazy;} tr[N << 2];
    private: auto Pushup(int rt) -> void {tr[rt].val = std::max(tr[ls].val, tr[rs].val);}
    private: auto Pushtag(int rt, int v) -> void {tr[rt].lazy += v; tr[rt].val += v;}
    private: auto Pushdown(int rt) -> void {
        if (tr[rt].lazy) {
            Pushtag(ls, tr[rt].lazy);
            Pushtag(rs, tr[rt].lazy);
            tr[rt].lazy = 0;
        } return void();
    }
    public: auto Build(int rt, int l, int r) -> void {
        tr[rt].val = tr[rt].lazy = 0;
        tr[rt].l = l, tr[rt].r = r;
        if (l == r) return void(tr[rt].val = l);
        int mid = (l + r) >> 1;
        Build(ls, l, mid); Build(rs, mid + 1, r);
        return Pushup(rt);
    }
    public: auto Update(int rt, int l, int r) -> void {
        if (l <= tr[rt].l && tr[rt].r <= r) return Pushtag(rt, -1);
        Pushdown(rt);
        int mid = (tr[rt].l + tr[rt].r) >> 1;
        if (l <= mid) Update(ls, l, r);
        if (r > mid) Update(rs, l, r);
        return Pushup(rt);
    }
    public: auto Query(int rt, int v) -> int {
        if (tr[rt].l == tr[rt].r) return tr[rt].l;
        Pushdown(rt);
        int mid = (tr[rt].l + tr[rt].r) >> 1, ans = 0;
        if (tr[ls].val >= v) ans = Query(ls, v);
        else ans = Query(rs, v);
        Pushup(rt); return ans;
    }
    #undef ls
    #undef rs
} TT;
// 初值均为0 
// 线段树节点维护这个区间有几个数已经插入 
// 支持单点插入 
// 支持查询区间插入的数的个数 查询从右往左第v个数
class SegmentTree2 { 
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    private: class TreeNode {public: int val, l, r;} tr[N << 2];
    private: auto Pushup(int rt) -> void {tr[rt].val = tr[ls].val + tr[rs].val;}
    public: auto Build(int rt, int l, int r) -> void {
        tr[rt].val = 0, tr[rt].l = l, tr[rt].r = r;
        if (l == r) return void(tr[rt].val = 0);
        int mid = (l + r) >> 1;
        Build(ls, l, mid); Build(rs, mid + 1, r);
        return Pushup(rt);
    }
    public: auto Insert(int rt, int x) -> void {
        if (tr[rt].l == tr[rt].r) return void(++ tr[rt].val);
        int mid = (tr[rt].l + tr[rt].r) >> 1;
        x <= mid ? (Insert(ls, x), 0) : (Insert(rs, x), 0);
        return Pushup(rt);
    }
    public: auto Query(int rt, int v) -> int {
        if (tr[rt].l == tr[rt].r) return tr[rt].l;
        int mid = (tr[rt].l + tr[rt].r) >> 1;
        if (tr[rs].val > v) return Query(rs, v);
        else return Query(ls, v - tr[rs].val);
    }
    public: auto Query(int rt, int l, int r) -> int {
        if (l <= tr[rt].l && tr[rt].r <= r) return tr[rt].val;
        int mid = (tr[rt].l + tr[rt].r) >> 1, ans = 0;
        if (l <= mid) ans += Query(ls, l, r);
        if (r > mid) ans += Query(rs, l, r);
        return ans;
    }
    #undef ls
    #undef rs
} T;
class Block {
    public: std::vector<pii> vec;
    public: auto Update(int x, int y) -> void {
        vec.emplace_back(x, std::min((int)vec.size() + 1, y));
        // 插在y位置或者末尾
    }
    public: auto Query() -> std::vector<int> {
        int n = vec.size();
        std::vector<int> p;
        p.resize(n + 1);
        std::reverse(vec.begin(), vec.end());      
        // 考虑从后往前做
        TT.Build(1, 1, n);
        for (auto [x, y] : vec) {
            int pos = TT.Query(1, y); // 求出当前这个数可以排到的位置（最多插y个人）
            p[pos] = x; // 固定位置
            TT.Update(1, pos, n); // 对当前位置到末尾 -1
        }
        for (int i = n; ~i; --i) if (p[i]) printf("%d ", p[i]); // 输出
        return p;
    }
} a[N];
int cnt;
std::vector<int>bel[N];
auto Solve(int x, int v) -> int {
    int y = T.Query(1, v); // 查询 1-v这里有几个连续段
    if (bel[x].empty() || bel[x].back() < y) return ++ cnt; // 如果说我这个组没有人 或者距离我太远 新增一个连续段
    return *std::lower_bound(bel[x].begin(), bel[x].end(), y); // 查找我能到的最前面的连续段
}
auto main() -> decltype(0) {
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    scanf("%d", &n);
    T.Build(1, 1, n);
    for (int i = 1, x, v; i <= n; ++i) {
        scanf("%d%d", &x, &v);
        int p = Solve(x, v); // 获取连续段编号
        if (bel[x].empty() || bel[x].back() < p) bel[x].emplace_back(p); // 新增连续段
        T.Insert(1, p); // 插入这个连续段
        a[p].Update(i, v - T.Query(1, p + 1, cnt) + 1);   
    }
    for (int i = 1; i <= cnt; ++i) a[i].Query();
    return 0;
}