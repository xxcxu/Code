/*
 * @Author: Maraschino 
 * @Date: 2022-09-13 14:52:28 
 * @Last Modified by:   Maraschino 
 * @Last Modified time: 2022-09-13 14:52:28 
 */
#include <bits/stdc++.h>
#define int long long
using pii = std::pair<int, int>;
static constexpr int N = 2e5 + 5;
int n, ans, p[N], d[N];
auto calc(int x) -> int {
    if (p[x] == x) return 0;
    if (p[x] > x) return p[x] - x;
    if (p[x] < x) return n - (x - p[x]);
}
std::priority_queue<int, std::vector<int>, std::greater<int>> q2;
std::priority_queue<int, std::vector<int>, std::less<int>> q1;
std::vector<int> v;
auto main() -> decltype(0) {
    scanf("%lld", &n);
    for (int i = 0; i < n; ++i) scanf("%lld", p + i);
    for (int i = 0; i < n; ++i) d[i] = (n - calc(i)) % n;
    for (int i = 0; i < n; ++i) ans += std::min(d[i], n - d[i]);
    int t = (n + 1) / 2;
    for (int i = 0; i < n; ++i) {
        if (d[i] < t - (n & 1)) q1.emplace(d[i]);
        else if ((n & 1) && d[i] == t - 1) v.emplace_back(d[i]);
        else q2.emplace(n - d[i]);
    }
    int ret = ans;
    for (int i = 0; i < n; ++i) {
        ret += (int)q1.size();
        ret -= (int)q2.size();
        if (n & 1) {
            while (v.size()) {
                q2.emplace((t - 1) + (i + 1));
                v.pop_back();
            }
            while (q1.size() && q1.top() + (i + 1) == t - 1) {
                v.emplace_back(t - 1);
                q1.pop();
            }
        } else {
            while (q1.size() && q1.top() + (i + 1) == t) {
                q2.emplace(t + (i + 1));
                q1.pop();
            }
        }
        while (q2.size() && q2.top() - (i + 1) == 0) {
            q1.emplace(-(i + 1));
            q2.pop();
        }
        ans = std::min(ans, ret);
    } return printf("%lld\n", ans), 0;
}