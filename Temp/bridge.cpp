# include <bits/stdc++.h>

using pii = std::pair<int, int>;
using LL = long long;

# define gc getchar
# define eb emplace_back
# define ep emplace

int read() {
	int x = 0, f = 0; char ch = gc();
	for (; !isdigit(ch); ch = gc()) f ^= (ch == '-');
	for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
	return f ? -x : x;
}

static const int N = 200005;

int n, m;
int a[N], b[N], d[N];
std::vector<pii> e[N];
bool vis[N];

void dfs(int x) {
	vis[x] = true;
	for (auto Z : e[x]) {
        const int &y = Z.first;
        const int &id = Z.second;
        if (!~d[id])
        {
            d[id] = x < y;
            if (!vis[y]) dfs(y);
        }
    } 
}

signed main() {
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
    n = read(), m = read();
    for (int i = 1; i <= m; ++i) a[i] = read();
	for (int i = 1; i <= m; ++i) b[i] = read();
	for (int i = 1; i <= m; ++i) {
		e[a[i]].eb(b[i], i);
		e[b[i]].eb(a[i], i);
	}
	std::memset(d, -1, sizeof d);
	for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
	for (int i = 1; i <= m; ++i) printf("%d", d[i] != (a[i] < b[i]));
	return 0;
}