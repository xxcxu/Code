#include <bits/stdc++.h>
#define eb emplace_back
using ull = unsigned long long;
static const int N = 1005;
int n, cnt, a[1 << 13];
ull w[N];
int count(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ++ ans;
    return ans;
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i < (1 << 13); ++i)
        if (count(i) == 6) a[++ cnt] = i;
    for (int i = 0; i < 13; ++i) {
        std::vector<int> v;
        for (int j = 1; j <= n; ++j)
            if (a[j] >> i & 1) v.eb(j);
        if ((int)v.size()) {
            printf("? %d ", (int)v.size());
            for (int j : v) printf("%d ", j); puts("");
            fflush(stdout);
            scanf("%llu", w + i);
        }
    }
    printf("! ");
    for (int i = 1; i <= n; ++i) {
        ull ans = 0;
        for (int j = 0; j < 13; ++j)
            if (!(a[i] >> j & 1)) ans |= w[j];
        printf("%llu ", ans);
    } return puts(""), 0;
}