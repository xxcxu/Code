#include <bits/stdc++.h>

template<typename DataType>
DataType read() {
    DataType t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}

#define int long long

static constexpr int N = 2e5 + 5;

int n, k, scc_cnt, ans;
int size[N], sum[N], val[N], indeg[N], bel[N];
int dfn[N], vis[N], in[N];

using pii = std::pair<int, int>;
std::vector<pii> e[N], g[N];

void tarjan(int x) {
    static int time_stamp = 0, top = 0;
    static int instack[N], stack[N], low[N];

    dfn[x] = low[x] = ++ time_stamp;
    instack[x] = true; stack[++ top] = x;

    for (auto [y, z] : e[x])
        if (!dfn[y]) tarjan(y), low[x] = std::min(low[x], low[y]);
        else if (instack[y]) low[x] = std::min(low[x], dfn[y]);

    if (dfn[x] == low[x]) {
        int u;
        ++ scc_cnt;
        do {
            u = stack[top --];
            bel[u] = scc_cnt;
            ++ size[scc_cnt];
            instack[u] = false;
        } while (u != x);
    }
}

void add(int u, int v, int w) {e[u].emplace_back(v, w);}

signed main() {
    n = read<int>(), k = read<int>();
    for (int i = 1; i <= k; ++i) {
        static int opt, x, y;
        opt = read<int>(), x = read<int>(), y = read<int>();
        switch(opt) {
            case 1: add(x, y, 0), add(y, x, 0); break;
            case 2: add(x, y, 1); break;
            case 3: add(y, x, 0); break;
            case 4: add(y, x, 1); break;
            case 5: add(x, y, 0); break;
            default: break;
        }
    }

    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);

    for (int i = 1; i <= n; ++i)
        for (auto &[j, k] : e[i]) {
            if (bel[i] != bel[j]) 
                g[bel[i]].emplace_back(bel[j], k), ++ indeg[bel[j]];
            else
                sum[bel[i]] += k;
        }
    for (int i = 1; i <= scc_cnt; ++i) if (sum[i] > 0) return puts("-1"), 0;
  
    std::queue<int> q;
    for (int i = 1; i <= scc_cnt; ++i) if (!indeg[i]) val[i] = 1, q.emplace(i);
    while (q.size()) {
        int x = q.front(); q.pop();
        for (auto &[y, z] : g[x]) {
            -- indeg[y]; val[y] = std::max(val[y], val[x] + z);
            if (!indeg[y]) q.emplace(y);
        }
    }
    for (int i = 1; i <= scc_cnt; ++i) ans += val[i] * size[i];
    return printf("%lld\n", ans), 0;
}