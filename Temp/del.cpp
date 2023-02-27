# include <bits/stdc++.h>

# define int long long

# define gc getchar
# define eb emplace_back

int read() {
	int x = 0, f = 0; char ch = gc();
	for (; !isdigit(ch); ch = gc()) f ^= (ch == '-');
	for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
	return f ? -x : x;
}

static const int N = 5005, inf = 1e18; 

int n, time_stamp;
int a[N], b[N], c[N];
int dep[N], min[N];
int l[N], r[N], redfn[N];
int dp[N][N];
std::vector<int> e[N];

void sie(int x, int fa) {
    dep[x] = dep[fa] + 1;
    l[x] = ++time_stamp;
    redfn[time_stamp] = x;

    for (int y : e[x]) if (y != fa) sie(y, x);

    r[x] = time_stamp;
}

int calc(int x, int l) {
    return 2 * a[x] * l + a[x] + b[x];
}

void dfs(int x, int fa) {

	int sum = 0;
	for (int y : e[x]) if (y != fa) dfs(y, x);
	for (int y : e[x]) if (y != fa) sum += min[y];
    dp[x][x] = c[x] + sum;
    for (int y : e[x]) if (y != fa) {
		for (int i = l[y]; i <= r[y]; ++i) {
            int p = redfn[i];
            dp[x][p] = std::min(dp[x][p], sum - min[y] + dp[y][p] + calc(p, dep[p] - dep[y]));
        }
	}

	min[x] = inf;
	for (int i = 1; i <= n; ++i) min[x] = std::min(min[x], dp[x][i]);
	return void();
}

signed main() {
	freopen("del.in", "r", stdin);
	freopen("del.out", "w", stdout);
	n = read();
	for (int i = 1; i < n; ++i) {
		static int u, v;
		u = read(), v = read();
		e[u].eb(v); e[v].eb(u);
	}
	for (int i = 1; i <= n; ++i)
		a[i] = read(), b[i] = read(), c[i] = read();

    sie(1, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) dp[i][j] = inf;
	dfs(1, 0);

    return printf("%lld\n", min[1]), 0;
}