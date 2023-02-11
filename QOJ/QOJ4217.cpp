#include <bits/stdc++.h>
static const int N = 5005;
int n, cnt, a[N];
char s[N][N];
int count(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ++ ans;
    return ans;
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= (1 << 14); ++i) if (count(i) == 7) a[++ cnt] = i;
    for (int i = 1; i < n; ++i, puts(""))
        for (int j = 1; j <= i; ++j) {
            int from = i + 1, to = j;
            if (s[i][j] == '0') std::swap(from, to);
            for (int c = 0; c < 14; ++c)
                if ((a[from] >> c & 1) && !(a[to] >> c & 1)) {
     /               putchar('a' + c);
                    break;
                }
        } return 0;
}