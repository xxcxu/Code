#include <bits/stdc++.h>
#define int long long
const int N = 1e6 + 5;
int n, a, b, ans, cnt;
struct node {int l, r;} segment[N << 1];
signed main() {
    scanf("%lld%lld%lld", &n, &a, &b);
    std::function<int(int, int)> Gcd = [&](int x, int y) {return !y ? x : Gcd(y, x % y);};
    int t = a / Gcd(a, b + 1) * b;
    for (int i = 1, l, r; i <= n; ++i) {
        scanf("%lld%lld", &l, &r);
        if (r - l + 1 >= t) return printf("%lld\n", t), 0;
        else {
            int L = l % t, R = r % t;
            if (L > R) segment[++ cnt] = {0, R}, segment[++ cnt] = {L, t - 1};
            else segment[++ cnt] = {L, R};
        }
    } 
    std::sort(segment + 1, segment + cnt + 1, [&](node a, node b) {return a.l < b.l;});
    int ans = 0, ll = segment[1].l, rr = segment[1].r; segment[++ cnt].l = t + 1;
    for (int i = 2; i <= cnt + 1; ++i) {
        if (rr < segment[i].l) ans += rr - ll + 1, ll = segment[i].l, rr = segment[i].r;
        else rr = std::max(rr, segment[i].r);
    } return printf("%lld\n",ans), 0;
}
