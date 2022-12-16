#pragma GCC optimize(3)
#include <bits/stdc++.h>
static constexpr int N = 5e4 + 5;
int n;
char str[N];
auto main() -> decltype(0) {
    #ifdef ONLINE_JUDGE
        freopen("string.in", "r", stdin);
        freopen("string.out", "w", stdout);
    #endif
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for (int i = 1; i <= n / 2; ++i) {
        int cnt = 0;
        for (int j = 1; j <= n - i; ++j) {
            if (str[j] == str[j + i]) ++ cnt;
            else cnt = 0;
            if (cnt == i) {
                for (int k = j + 1; k <= n - i; ++k)
                    str[k] = str[k + i];
                n -= i; i = 0; break;
            }
        }
    }
    str[n + 1] = 0;
    puts(str + 1);
	return 0;
}