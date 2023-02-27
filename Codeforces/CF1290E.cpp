# include <bits/stdc++.h>

# define int long long

static const int N = 150005;

int n, a[N], pos[N], ans[N];
FILE *fin, *fout, *ferr;

class SGT {
    # define ls (x << 1)
    # define rs (x << 1 | 1)

    private:
        class TreeNode {
            public:
                int sum, l, cnt, mx1, mx2;
                TreeNode(int sum = 0, int l = 0, int cnt = 0, int mx1 = 0, int mx2 = 0):
                    sum(sum), l(l), cnt(cnt), mx1(mx1), mx2(mx2) {}
                TreeNode operator + (TreeNode &a) {
                    TreeNode o = TreeNode(0, 0, 0, 0, 0);
                    o.sum = sum + a.sum;
                    o.l = l + a.l;
                    if (mx1 > a.mx1)
                    {
                        o.mx1 = mx1;
                        o.mx2 = std::max(mx2, a.mx1);
                        o.cnt = cnt;
                    }
                    if (mx1 < a.mx1)
                    {
                        o.mx1 = a.mx1;
                        o.mx2 = std::max(mx1, a.mx2);
                        o.cnt = a.cnt;
                    }
                    if (mx1 == a.mx1)
                    {
                        o.mx1 = mx1;
                        o.mx2 = std::max(mx2, a.mx2);
                        o.cnt = cnt + a.cnt;
                    }
                    return o;
                }
        } tr[N << 2];
        
        int tag[N << 2], cov[N << 2];
    public:
        void reset(int x) {
            tr[x] = TreeNode(0, 0, 0, 0, -1);
            tag[x] = 0;
            cov[x] = -1;
            return void();
        }
        void pushtag(int x, int v) {
            if (tr[x].l == 0)
                return void();
            tr[x].sum += tr[x].l * v;
            tr[x].mx1 += v;
            if (tr[x].mx2 != -1)
                tr[x].mx2 += v;
            tag[x] += v;
            if (cov[x] != -1)
                cov[x] += v;
            return void();
        }
        void pushtag2(int x, int v) {
            if (tr[x].l == 0)
                return void();
            if (v > tr[x].mx1)
                return void();
            tr[x].sum -= (tr[x].mx1 - v) * tr[x].cnt;
            tr[x].mx1 = v;
            cov[x] = v;
            return void();
        }
        void pushup(int x) {
            return tr[x] = tr[ls] + tr[rs], void();
        }
        void pushdown(int x) {
            if (tr[x].l == 0)
                return void();
            if (tag[x])
            {
                pushtag(ls, tag[x]);
                pushtag(rs, tag[x]);
                tag[x] = 0;
            }
            if (cov[x] != -1)
            {
                pushtag2(ls, cov[x]);
                pushtag2(rs, cov[x]);
                cov[x] = -1;
            }
            return void();
        }
        void build(int x, int l, int r) {
            reset(x);
            if (l == r)
                return void();
            int mid = (l + r) >> 1;
            build(ls, l, mid);
            build(rs, mid + 1, r);
            return void();
        }
        void getmin(int x, int l, int r, int ql, int qr, int v) {
            if (ql <= l && r <= qr)
                if (tr[x].mx2 < v) {
                    pushtag2(x, v);
                    return void();
                }
            int mid = (l + r) >> 1;
            pushdown(x);
            if (ql <= mid)
                getmin(ls, l, mid, ql, qr, v);
            if (qr >  mid)
                getmin(rs, mid + 1, r, ql, qr, v);
            return pushup(x);
        }
        void update(int x, int l, int r, int ql, int qr, int v) {
            if (ql <= l && r <= qr)
                return pushtag(x, v);
            int mid = (l + r) >> 1;
            pushdown(x);
            if (ql <= mid)
                update(ls, l, mid, ql, qr, v);
            if (qr >  mid)
                update(rs, mid + 1, r, ql, qr, v);
            return pushup(x);
        }
        void insert(int x, int l, int r, int p, int v) {
            if (l == r) {
                tr[x] = TreeNode(v, 1, 1, v, -1);
                return void();
            }
            int mid = (l + r) >> 1;
            pushdown(x);
            p <= mid ? insert(ls, l, mid, p, v) : insert(rs, mid + 1, r, p, v);
            return pushup(x);
        }
        int query(int x, int l, int r, int ql, int qr) {
            if (ql <= l && r <= qr)
                return tr[x].l;
            int mid = (l + r) >> 1, ans = 0;
            pushdown(x);
            if (ql <= mid)
                ans += query(ls, l, mid, ql, qr);
            if (qr >  mid)
                ans += query(rs, mid + 1, r, ql, qr);
            return ans;
        }
        int query() {
            return tr[1].sum;
        }

} t;

void solve() {
    for (int i = 1; i <= n; ++i) pos[a[i]] = i;
    t.build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        int p = pos[i];
        if (p < n) t.update(1, 1, n, p + 1, n, 1);
        if (p > 1) {
            int x = t.query(1, 1, n, 1, p - 1) + 1;
            t.getmin(1, 1, n, 1, p - 1, x);
        }
        t.insert(1, 1, n, p, i + 1);
        ans[i] += t.query();
    }
    return void();
}

signed main() {
    // fin = stdin;
    // fout = stdout;
    // ferr = stderr;
    fin = fopen("Input.txt", "r");
    fout = fopen("Output.txt", "w+");
    ferr = fopen("Debug.txt", "w+");

    fscanf(fin, "%lld", &n);
    for (int i = 1; i <= n; ++i) fscanf(fin, "%lld", a + i);
    solve();
    std::reverse(a + 1, a + n + 1);
    solve();
    for (int i = 1; i <= n; ++i) fprintf(fout, "%lld\n", ans[i] - i * (i + 2));
    return 0;
}
