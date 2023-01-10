#include <bits/stdc++.h>
static const int N = 200005, inf = 998244353;
int n, k, cnt, tot, now, a[N], l[N], r[N], val[N];
char s[N], d[N << 1];
bool choose[N];
void dfs(int x) {
    if (!x) return void();
    dfs(l[x]);
    a[++ cnt] = x;
    dfs(r[x]);
}
void dfs2(int x, int c) {
    if (!x) return void();
    dfs2(l[x], c + 1);
    ++ now;
    d[tot ++] = s[x];
    if (choose[l[x]]) choose[x] = true, d[tot ++] = s[x], dfs2(r[x], 1);
    else if (val[now] && c <= k) choose[x] = true, d[tot ++] = s[x], k -= c, dfs2(r[x], 1);
    else dfs2(r[x], inf);
}
signed main() {
    scanf("%d%d%s", &n, &k, s + 1);
    for (int i = 1; i <= n; ++i) scanf("%d%d", l + i, r + i);
    dfs(1);
    for (int i = n; i >= 1; --i) 
        val[i] = (s[a[i]] == s[a[i + 1]] ? val[i + 1] : s[a[i]] < s[a[i + 1]]);
    dfs2(1, 1);
    puts(d);
}