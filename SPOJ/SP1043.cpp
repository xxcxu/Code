#include <bits/stdc++.h>
static const int N = 200005;
int n, m, a[N], pos[N];
int p[N][32], s[N][32];
void build(int x, int l, int r, int d) {
    if (l == r) {
        pos[l] = x;
        return void();
    }
    int mid = (l + r) >> 1;
    int sum, sum2;
    p[d][mid] = s[d][mid] = sum = sum2 = a[mid];
    sum2 = std::max(sum2, 0);
    for (int i = mid - 1; i >= l; --i) {
        sum += a[i]; sum2 += a[i];
        sum2 = std::max(sum2, 0);
        s[d][i] = std::max(s[d][i + 1], sum);
        p[d][i] = std::max(p[d][i + 1], sum2);
    }
    p[d][mid + 1] = s[d][mid + 1] = sum = sum2 = a[mid + 1];
    sum2 = std::max(sum2, 0);
    for (int i = mid + 2; i <= r; ++i) {
        sum += a[i]; sum2 += a[i];
        sum2 = std::max(sum2, 0);
        s[d][i] = std::max(s[d][i - 1], sum);
        p[d][i] = std::max(p[d][i - 1], sum2);
    }
    build(x << 1, l, mid, d + 1); build(x << 1 | 1, mid + 1, r, d + 1);
    return void();
}
int query(int l, int r) {
    int d = std::log2(pos[l]) - std::log2(pos[l] ^ pos[r]);
    return std::max({p[d][l], p[d][r], s[d][l] + s[d][r]}); 
}
signed main() {
    scanf("%d", &n); int k = 1;
    while (k < n) k <<= 1;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    build(1, 1, k, 1);
    scanf("%d", &m);
    while (m --) {
        static int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }
    return 0;
}