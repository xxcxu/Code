#include <bits/stdc++.h>
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
static constexpr int N = 1e5 + 5, inf = 0x3f3f3f3f;
int n, m, ans, s[N], t[N], len[N];
void cmin(int &x, int y) {if (y < x) x = y;}
class SegmentTree {
    private: int min[N << 2];
    private: int ls(int x) {return x << 1;}
    private: int rs(int x) {return x << 1 | 1;}
    private: void pushup(int x) {min[x] = std::min(min[ls(x)], min[rs(x)]);}
    public: SegmentTree() {std::memset(min, 0, sizeof min);}
    public: void build(int x, int l, int r) {
        min[x] = inf;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(ls(x), l, mid); build(rs(x), mid + 1, r);
    }
    public: void update(int x, int l, int r, int p, int v) {
        if (l == r) return void(min[x] = v);
        int mid = (l + r) >> 1;
        if (p <= mid) update(ls(x), l, mid, p, v);
        else update(rs(x), mid + 1, r, p, v);
        pushup(x);
    }
    public: int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return min[x];
        int mid = (l + r) >> 1, ans = inf;
        if (ql <= mid) cmin(ans, query(ls(x), l, mid, ql, qr));
        if (qr > mid) cmin(ans, query(rs(x), mid + 1, r, ql, qr));
        return ans;
    }
} tree;
signed main() {
    freopen("cell.in", "r", stdin);
    freopen("cell.out", "w", stdout);
    read(n, m);
    for (int i = 1; i <= m; ++i) read(s[i], t[i]), len[i] = t[i] - s[i] + 1;
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, inf));
    for (int i = 1; i + len[1] - 1 <= n; ++i) dp[1][i] = std::abs(s[1] - i);
    for (int i = 2; i <= m; ++i) {
        tree.build(1, 1, n);
        for (int j = 1; j <= n; ++j)
            tree.update(1, 1, n, j, dp[i - 1][j]);
        for (int j = 1; j + len[i] - 1 <= n; ++j) {
            int l = std::max(j - len[i - 1] + 1, 1);
            int r = std::min(j + len[i] - 1, n - len[i - 1] + 1);
            dp[i][j] = tree.query(1, 1, n, l, r) + std::abs(s[i] - j);
        }
    }
    ans = inf;
    for (int i = 1; i + len[m] - 1 <= n; ++i) cmin(ans, dp[m][i]);
    return printf("%d\n", ans), 0;
}