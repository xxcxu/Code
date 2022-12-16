#include <bits/stdc++.h>
#define int long long
using pii = std::pair<int, int>;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m, r, k; double ans;
std::map<pii, bool> vis;
class point {
    public: int x, y; double c;
    public: point(int x = 0, int y = 0, double c = 0):
        x(x), y(y), c(c) {}
    public: bool operator < (point a) const {return c < a.c;}
};
std::priority_queue<point> q;
double calc(point x) {
    int res = (std::min(n, x.x + r - 1) - std::max(x.x, r) + 1) * (std::min(m, x.y + r - 1) - std::max(x.y, r) + 1);
    return 1.0 * res / (n - r + 1) / (m - r + 1);
}
bool check(point x) {
    if (x.x < 1 || x.x > n || x.y < 1 || x.y > m) return false;
    if (vis.count(pii(x.x, x.y))) return false;
    return true;
}
signed main() {
    scanf("%lld%lld%lld%lld", &n, &m, &r, &k);
    point s(n / 2 + 1, m / 2 + 1);
    s.c = calc(s); vis[pii(s.x, s.y)] = true;
    q.emplace(s);
    for (int i = 1; i <= k; ++i) {
        point x = q.top(); q.pop();
        ans += x.c; 
        for (int d = 0; d < 4; ++d) {
            point dx = point(x.x + dir[d][0], x.y + dir[d][1]);
            if (!check(dx)) continue; dx.c = calc(dx);
            q.emplace(dx); vis[pii(dx.x, dx.y)] = true;
        }
    } return printf("%.10lf\n", ans), 0;
}