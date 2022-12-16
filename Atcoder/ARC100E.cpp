#include <bits/stdc++.h>
static constexpr int N = 1 << 19;
int n, a[N], ans[N];
class Node {public: int max, minimax;} f[N];
auto Update(int x, int y) -> void {
    if (a[y] > a[f[x].max]) {
        f[x].minimax = f[x].max;
        f[x].max = y;
    } else if (a[y] > a[f[x].minimax] && y != f[x].max)
        f[x].minimax = y;
}
auto main() -> decltype(0) {
    scanf("%d", &n);
    for (int i = 0; i < (1 << n); ++i) {
        scanf("%d", a + i);
        f[i].minimax = N - 1;
        Update(i, i);
    }
    for (int i = 0; i < (1 << n); ++i)
        for (int j = 0; j < n; ++j)
            if (i >> j & 1) {
                Update(i, f[i ^ (1 << j)].max);
                Update(i, f[i ^ (1 << j)].minimax);
            }
    for (int i = 1; i < (1 << n); ++i) {
        ans[i] = a[f[i].max] + a[f[i].minimax];
        ans[i] = std::max(ans[i], ans[i - 1]);
        printf("%d\n", ans[i]);
    } return 0;
}