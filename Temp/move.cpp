#include <bits/stdc++.h>
#define eb emplace_back
#define all(x) x.begin(), x.end()
static constexpr int N = 2e5 + 5;
int n, q, a[N], p[N], d[N], bel[N];
char str[N];
bool check1(int x) {
    for (int i = 1; i <= q; ++i) {
        if (p[i] - 'A' != bel[x]) continue;
        if (d[i] == 'L') -- x;
        else ++ x;
        if (x > n) return false;
        if (x < 1) return true;
    } return false;
}
bool check2(int x) {
    for (int i = 1; i <= q; ++i) {
        if (p[i] - 'A' != bel[x]) continue;
        if (d[i] == 'L') -- x;
        else ++ x;
        if (x < 1) return false;
        if (x > n) return true;
    } return false;
}
int binary1() {
    int l = 1, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check1(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    } return ans;
}
int binary2() {
    int l = 1, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check2(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    } return ans;
}
signed main() {
    freopen("move.in", "r", stdin);
    freopen("move.out", "w", stdout);
    scanf("%d%d", &n, &q);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i) bel[i] = str[i] - 'A';
    for (int i = 1; i <= q; ++i) {
        static char ch;
        ch = getchar();
        while (!isalpha(ch)) ch = getchar(); p[i] = ch;
        ch = getchar();
        while (!isalpha(ch)) ch = getchar(); d[i] = ch;
    }
    int t1 = binary1(); t1 = t1 == -1 ? 0 : t1;
    int t2 = binary2(); t2 = t2 == -1 ? n + 1 : t2;
    printf("%d\n", t2 - t1 - 1);
    return 0;
}