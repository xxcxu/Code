#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 12e2 + 5, M = 12e4 + 5, inf = 0x3f3f3f3f;
int n, m, s, t, cnt = 1, level;
int ht[N], ex[N], gap[N], last[N];
std::stack<int> b[N << 1];
struct Edge {int u, v, w, next;} e[M << 1];
auto Addedge(int u, int v, int w) -> void {e[++ cnt] = (Edge){u, v, w, last[u]}; last[u] = cnt;}
auto Addflow(int u, int v, int w) -> void {Addedge(u, v, w); Addedge(v, u, 0);}
auto Push(int x) -> int {
    bool init = x == s;
    for (int i = last[x]; i; i = e[i].next) {
        int &y = e[i].v, &z = e[i].w;
        if (!z || !init && ht[x] != ht[y] + 1) continue;
        int k = init ? z : std::min(z, ex[x]);
        if ((y ^ s) && (y ^ t) && !ex[y])
            b[ht[y]].emplace(y), level = std::max(level, ht[y]);
        ex[x] -= k, ex[y] += k, e[i].w -= k, e[i ^ 1].w += k;
        if (!ex[x]) return 0;
    } return 1;
}
auto Relabel(int x) -> void {
    ht[x] = inf;
    for (int i = last[x]; i; i = e[i].next)
        if (e[i].w)
            ht[x] = std::min(ht[x], ht[e[i].v]);
    if (++ ht[x] < n) {
        b[ht[x]].emplace(x);
        level = std::max(level, ht[x]); 
    }
}
auto Unicom() -> bool {
    std::memset(ht, 0x3f, sizeof ht);
    std::queue<int> q;
    q.emplace(t), ht[t] = 0;
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i = last[x]; i; i = e[i].next) {
            int &y = e[i].v;
            if (e[i ^ 1].w && ht[y] > ht[x] + 1)
                ht[y] = ht[x] + 1, q.emplace(y);
        }
    } return ht[s] != inf;
}
auto Select() -> int {
    while (!(int)(b[level].size()) && level > -1) -- level;
    return ~level ? b[level].top() : 0;
}
auto Hlpp() -> int {
    if (!Unicom()) return 0;
    std::memset(gap, 0, sizeof gap);
    for (int i = 1; i <= n; ++i)
        if (ht[i] != inf) ++ gap[ht[i]];
    ht[s] = n; Push(s);
    int x;
    while ((x = Select())) {
        b[level].pop();
        if (Push(x)) {
            if (!-- gap[ht[x]])
                for (int i = 1; i <= n; ++i)
                    if ((i ^ s) && (i ^ t) && ht[i] > ht[x] && ht[i] < n + 1)
                        ht[i] = n + 1;
            Relabel(x);
        }
    } return ex[t];
}
auto main() -> decltype(0) {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        Addflow(u, v, w);
    }
    printf("%d\n", Hlpp());
    return 0;
}