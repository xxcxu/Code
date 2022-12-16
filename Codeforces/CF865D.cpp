#include <bits/stdc++.h>
#define int long long
int n, ans;
std::priority_queue<int, std::vector<int>, std::greater<int>> q;
signed main() {
    scanf("%lld", &n);
    for (int i = 1, x; i <= n; ++i) {
        scanf("%lld", &x);
        if (q.size() && q.top() < x) {
            ans += x - q.top();
            q.pop(); q.emplace(x);
        } q.emplace(x);
    } return printf("%lld\n", ans), 0;
}