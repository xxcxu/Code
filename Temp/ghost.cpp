# include <bits/stdc++.h>

using pii = std::pair<int, int>;

# define fi first
# define se second
# define gc getchar
# define eb emplace_back
# define ep emplace
# define R ((1 << k) - 1)

int read() {
	int x = 0, f = 0; char ch = gc();
	for (; !isdigit(ch); ch = gc()) f ^= (ch == '-');
	for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
	return f ? -x : x;
}

static const int N = 10005, S = 1 << 8;
static const int inf = 0x3f3f3f3f;

int n, m, k, E, T;
int p[N], d[N][S], dp[2][S];
bool vis[N];
std::vector<pii> e[N], v[8];

signed main() {
    freopen("ghost.in", "r", stdin);
    freopen("ghost.out", "w", stdout);
    n = read(), m = read(), k = read();
    for (int i = 1; i <= m; ++i) {
		static int u, v, w;
		u = read(), v = read(), w = read();
		e[u].eb(v, w); e[v].eb(u, w);   
	}
	E = read(), T = read();
    for (int i = 1; i <= E; ++i) {
        static int P, x, t;
		P = read() - 1, x = read(), t = read();
		v[P].eb(t, x);
    }
	p[0] = read(); p[1] = read();
	std::memset(dp, 0x3f, sizeof dp);
    for (int _ = 0; _ <= 1; ++_) {
        std::memset(d, 0x3f, sizeof d);
		std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
        d[p[_]][0] = 0;
        for (int S = 0; S <= R; ++S) {
            for (int i = 1; i <= n; ++i) vis[i] = 0, q.ep(d[i][S], i);
            while (q.size()) {
                int x = q.top().se; q.pop();
                if (vis[x]) continue; vis[x] = true;
                for (auto [y, z] : e[x])
            for (int i = 0; i < k; ++i)
                if (!(S >> i & 1))
                    for (auto [t, x] : v[i])
                        if (d[x][S] <= t)
                            d[x][S | (1 << i)] = std::min(d[x][S | (1 << i)], t);
            for (int i = 1; i <= n; ++i)
                dp[_][S] = std::min(dp[_][S], d[i][S]);
        }
    }
    int ans = 0x7fffffff;
    for (int S = 0; S <= R; ++S)
        ans = std::min(ans, std::max(dp[0][S], dp[1][R ^ S]));
	if (ans > T) ans = -1;
    return printf("%d\n", ans), 0;
}
