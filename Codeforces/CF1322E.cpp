#include<bits/stdc++.h>
#define eb emplace_back
#define ep emplace
static const int N = 500005;
int n, m, res;
int a[N], b[N], d[N], ans[N];
std::vector<int> c[N];
std::set<int> s1, s2;
void insert(int x) {
    if (x > 1 && !d[x - 1]) s1.erase(x - 1); else s1.insert(x - 1);
    if (x < n && !d[x + 1]) s1.erase(x);     else s1.insert(x);
    d[x] = 1;
}
void change(int l, int r, int x) {
    auto it = s2.lower_bound(l);
    while (it != s2.end() && *it <= r) {
        ans[*it] = x;
        s2.erase(it);
        it = s2.lower_bound(l);
    }
}
void update(int x, int y) {
    auto it = s1.lower_bound(x);
    int r = (*it), l = (*--it) + 1;
    res = std::max(res, (r - l) / 2);
    int mid = (l + r) >> 1;
    if (d[l]) change(l, mid, y);
    if (d[r]) change(mid + 1, r, y);
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    std::sort(b + 1, b + n + 1);
    m = std::unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(b + 1, b + m + 1, a[i]) - b;
    for (int i = 1; i <= n; ++i) c[a[i]].eb(i);
    for (int i = 0; i <= n; ++i) s1.ep(i);
    for (int i = 1; i <= n; ++i) s2.ep(i);
    for (int i = 1; i <= m; ++i) {
        for (int j : c[i]) insert(j);
        for (int j : c[i]) {
            update(j, i);
            if (j > 1) update(j - 1, i);
            if (j < n) update(j + 1, i);
        }
    }
    printf("%d\n", res);
    for (int i = 1; i <= n; ++i) printf("%d ", b[ans[i]]);
    return 0;
}