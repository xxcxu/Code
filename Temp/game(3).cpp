#include <bits/stdc++.h>
static constexpr int N = 2e5 + 5, M = 1e6;
int n, q, s = 2e6, a[N];
std::deque<int> que;
signed main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) scanf("%d", a + i);
    for (int i = 0; i <= s; ++i) que.push_back(i);
    for (int i = 3; i < n; ++i) {
        std::vector<int> v;
        for (int j = 1; j <= a[i]; ++j) v.emplace_back(que[j]), que.pop_back();
        for (int j : v) que.push_front(j);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        scanf("%d", a + n);
        printf("%d\n", (a[n] <= s ? que[a[n]] : a[n] - s + que[s]) + a[1] - a[2]);
    }
    return 0;
}