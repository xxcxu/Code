#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e5 + 5;
int n;
class node {public: int p, m;} p[N];
void solve() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld%lld", &p[i].p, &p[i].m);
    std::sort(p + 1, p + n + 1, [&](const node &a, const node &b) {
        if (a.p != b.p) return a.p < b.p;
        else return a.m < b.m;
    });
    p[n + 1] = (node){(int)1e9, 0};
    std::priority_queue<int> heap;
    for (int i = 0, j = 1; i < n; ++i) {
        while (p[j].p == i) heap.emplace(p[j ++].m);
        if (heap.size()) heap.pop();
    }
    int sum = 0;
    while (heap.size()) sum += heap.top(), heap.pop();
    printf("%lld\n", sum);
}
signed main() {
    int t; scanf("%lld", &t);
    while (t--) solve();
}