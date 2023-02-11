#include <bits/stdc++.h>
static const int N = 200005;
int n, q, s0[N], s1[N];
char s[N];
signed main() {
    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i) {
        if (s[i] == s[i - 1]) {
            s0[i] += s[i] == '0';
            s1[i] += s[i] == '1';
        }
    }
    for (int i = 1; i <= n; ++i) s0[i] += s0[i - 1];
    for (int i = 1; i <= n; ++i) s1[i] += s1[i - 1];
    while (q--) {
        static int l, r;
        scanf("%d%d", &l, &r);
        int max0 = s0[r] - s0[l];
        int max1 = s1[r] - s1[l];
        printf("%d\n", std::max(max0, max1) + 1);
    } return 0;
}