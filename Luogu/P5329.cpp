#include <bits/stdc++.h>
const int N = 1e6 + 5;
int n, f[N], id[N];
char s[N]; 
auto cmp(int x, int y) -> bool {
    if (x > y) return !cmp(y, x);
    if (f[x] > y) return true;
    return s[f[x]] < s[f[x] - 1];
}
auto main() -> decltype(0) {
    scanf("%d%s", &n, s + 1);
    f[n] = n + 1;
    for (int i = n - 1; i; --i)
        if (s[i] == s[i + 1])
            f[i] = f[i + 1];
        else
            f[i] = i + 1;
    for (int i = 1; i <= n; ++i) id[i] = i;
    std::sort(id + 1, id + n + 1, cmp);
    for (int i = 1; i <= n; ++i) printf("%d%c", id[i], " \n"[i == n]);
    return 0;
}