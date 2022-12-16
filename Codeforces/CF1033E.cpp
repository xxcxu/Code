#include <bits/stdc++.h>
const int N = 6e2 + 5;
int n;
int vis[N], dep[N], anc[N];
std::queue<int> q;
int Query(std::vector<int> v) {
    int n = v.size();
    if (n < 2) return 0;
    printf("? %d\n", n);
    for (int i = 0; i < n; ++i) printf("%d%c", v[i], i == n - 1 ? '\n' : ' ');
    fflush(stdout); int x;
    scanf("%d", &x); return x;
}
void Update(int x, int fa) {
    if (vis[x]) return;
    vis[x] = true; dep[x] = dep[fa] + 1; anc[x] = fa; q.emplace(x);
}
void Calc(int x, std::vector<int> v) {
    if (!(int)(v.size())) return;
    int m1 = Query(v);
    v.emplace_back(x);
    int m2 = Query(v);
    if (m1 == m2) return;
    v.pop_back();
    if (v.size() == 1) return Update(v.front(), x);
    int mid = v.size() / 2;
    std::vector<int> v1, v2;
    for (int i = 0; i < mid; ++i) v1.emplace_back(v[i]);
    for (int i = mid; i < v.size(); ++i) v2.emplace_back(v[i]);
    Calc(x, v1); Calc(x, v2);
}
void Find(int x, int y) {
    int lca = 0, a = x, b = y;
    while (a ^ b) {
        if (dep[a] < dep[b]) std::swap(a, b);
        a = anc[a];
    } lca = a;
    std::vector<int> ans;
    for (int i = x; i ^ lca; i = anc[i]) ans.emplace_back(i); ans.emplace_back(lca);
    std::reverse(ans.begin(), ans.end());
    for (int i = y; i ^ lca; i = anc[i]) ans.emplace_back(i);
    printf("N %d\n", ans.size());
    for (int v : ans) printf("%d ", v);
    exit(0);
}
void Solve(std::vector<int> v) {
    if (v.size() <= 1) return void();
    if (v.size() == 2) return Find(v[0], v[1]);
    while (true) {
        random_shuffle(v.begin(), v.end());
        int mid = (v.size() + 1) >> 1;
        std::vector<int> v1 = v; v1.resize(mid);
        if (Query(v1)) return Solve(v1);
    }
}
signed main() {
    scanf("%d", &n); Update(1, 0);
    while (q.size()) {
        int x = q.front(); q.pop();
        std::vector<int> v;
        for (int i = 1; i <= n; ++i) if (!vis[i]) v.emplace_back(i);
        Calc(x, v);
    } std::vector<int> v[2];
    for (int i = 1; i <= n; ++i) v[dep[i] & 1].emplace_back(i);
    if (Query(v[0])) Solve(v[0]);
    else if (Query(v[1])) Solve(v[1]);
    printf("Y %d\n", v[0].size());
    for (int vi : v[0]) printf("%d ", vi);
    return 0;
}