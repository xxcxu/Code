#include <bits/stdc++.h>
#define eb emplace_back
using pii = std::pair<int, int>;
static const int N = 1000005;
int n, m, k, h[N], sum[N], tag[N];
int a[N], b[N];
char op[N][2];
std::vector<int> st[N];
void insert(int l, int r, int b) {
    for (int i = l; i <= r; ++i) 
        for (int j = 1; j <= b; ++j)
            st[i].eb(1);
}
void erase(int l, int r, int b) {
    for (int i = l; i <= r; ++i) 
        for (int j = 1; j <= b; ++j)
            if (st[i].size()) st[i].pop_back();
}
void reback(int x, int t) {
    for (int i = t - 1; i >= t - x; --i) {
        if (op[i][0] == '+')  erase(1, a[i], b[i]);
        else if (op[i][0] != 'R' && op[i][0] != '?') insert(a[i], m, b[i]);
    } return void();
}
pii query(int x) {
    for (int i = 1; i <= m; ++i) k = std::max(k, (int)st[i].size());
    for (int i = 1; i <= k; ++i) h[i] = 0;
    for (int i = 1; i <= m; ++i) {
        int sz = st[i].size();
        for (int j = 1; j <= sz; ++j) ++ h[j];
    }
    for (int i = 1; i <= m; ++i) {
        int sz = st[i].size();
        for (int j = 1; j <= sz; ++j)
            if ((sz - j) + (h[j] - i) + 1 == x) return pii(i, j);
    }
    return pii(-1, -1);
}
signed main() {
    freopen("stairs.in", "r", stdin);
    freopen("stairs.out", "w", stdout);
    scanf("%d", &n);
     for (int i = 1; i <= n; ++i) {
        scanf("%s", op[i]);
        if (op[i][0] == '+') scanf("%d%d", &a[i], &b[i]);
        else if (op[i][0] == 'R') scanf("%d", &a[i]); 
        else if (op[i][0] == '?') scanf("%d", &a[i]);       
        else scanf("%d%d", &a[i], &b[i]);
    }
    for (int i = 1; i <= n; ++i) {
        if (op[i][0] == 'R') continue;
        if (op[i][0] == '?') continue;
        m = std::max(m, a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        if (op[i][0] == '+') insert(1, a[i], b[i]);
        else if (op[i][0] == 'R') reback(a[i], i);e
        else if (op[i][0] == '?') {auto p = query(a[i]); printf("%d %d\n", p.first, p.second);}
        else erase(a[i], n, b[i]);
    }
    return 0;
}
