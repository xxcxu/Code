#include <bits/stdc++.h>
#define eb emplace_back
#define all(a) a.begin(), a.end()
using ll = long long;
static constexpr int N = 2e5 + 5;
int n, m, k, L;
int a[N], b[N], e[N], f[N], g[N];

class TreeArray {
    private: int s[N];
    private: int lowbit(int x) {return x & -x;}
    public: void add(int x, int v) {for (; x <= n; x += lowbit(x)) s[x] += v;}
    public: int ask(int x) {
        int ans = 0; 
        for (; x; x -= lowbit(x)) ans += s[x];
        return ans;
    }
} bit_tree;

int ask(const std::vector<int> &a, const std::vector<int> &b) {
    for (int i = 0; i < (int)b.size(); ++i) f[b[i]] = i + 1;
    for (int i = 0; i < (int)a.size(); ++i) g[i + 1] = f[a[i]];

    int ret = 0, n = (int)a.size();
    for (int i = 1; i <= n; ++i) {
        if (((i - 1) - bit_tree.ask(g[i] - 1)) & 1) ret ^= 1;
        bit_tree.add(g[i], 1);
    } 
    for (int i = 1; i <= n; ++i)
        bit_tree.add(g[i], -1);
    return ret;
}

bool check() {
    if (n != m) return false;

    std::vector<int> c, d, cc, dd, ans;
    for (int i = 1; i <= n; ++i) c.eb(a[i]);
    for (int i = 1; i <= m; ++i) d.eb(b[i]);
    
    cc = c, dd = d;
    std::sort(all(c)); std::sort(all(d));
    if (c != d) return false;
    c = cc, d = dd;
    
    for (int i = 0; i < k; ++i) {
        cc.clear(); dd.clear();
        for (int j = i ? i : k; j <= n; j += k)
            cc.eb(a[j]), dd.eb(b[j]);
        
        c = cc, d = dd;
        std::sort(all(c)), std::sort(all(d));
        if (c != d) return false;
        
        bool uniqu = false;
        if (std::unique(all(c)) != c.end()) uniqu = true;
        
        if (!uniqu) ans.eb(ask(cc, dd));
    }

    if (!(int)ans.size()) return true;

    int col = *ans.begin();
    for (int x : ans) if (x != col) return false;
    return true;
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) scanf("%d", b + i);
    scanf("%d", &k);
    L = 0;
    for (int i = 1; i <= n; ++i) e[++ L] = a[i];
    for (int i = 1; i <= m; ++i) e[++ L] = b[i];
    std::stable_sort(e + 1, e + L + 1);
    L = std::unique(e + 1, e + L + 1) - e - 1;
    for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(e + 1, e + L + 1, a[i]) - e;
    for (int i = 1; i <= m; ++i) b[i] = std::lower_bound(e + 1, e + L + 1, b[i]) - e;
    puts(check() ? "YES" : "NO");
}   


                                                                                                                                      signed main() {
    freopen("yinrier.in", "r", stdin);
    freopen("yinrier.out",  "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
}