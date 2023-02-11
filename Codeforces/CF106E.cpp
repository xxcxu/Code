#include <bits/stdc++.h>
#define db double
static const int N = 105;
static const db eps = 1e-10;
db n, sx, sy, sz;
struct Node {
    db x, y, z;
    Node(db x = 0, db y = 0, db z = 0): x(x), y(y), z(z) {}
} a[N];
db sqr(db x) {return x * x;}
db dis(Node a, Node b) {return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);}
Node sa() {
    Node P(sx / n, sy / n, sz / n); db ans = -1;
    for (db tmp = 1; tmp > eps; tmp *= 0.9972) {
        db max = -1; int p = -1;
        for (int i = 1; i <= n; ++i)
            if (dis(P, a[i]) > max) max = dis(P, a[p = i]);
        P.x += (a[p].x - P.x) * tmp;
        P.y += (a[p].y - P.y) * tmp;
        P.z += (a[p].z - P.z) * tmp;
    }
    return P;
}
signed main() {
    scanf("%lf", &n);
    for (int i = 1; i <= n; ++i) scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].z);
    for (int i = 1; i <= n; ++i) sx += a[i].x, sy += a[i].y, sz += a[i].z;
    Node ans = sa();
    return printf("%.8lf %.8lf %.8lf\n", ans.x, ans.y, ans.z), 0;
}