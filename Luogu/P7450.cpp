# include <bits/stdc++.h>

# define eb emplace_back
# define ep emplace

using pii = std::pair<int, int>;

static const int N = 305, inf = 0x3f3f3f3f, S = (1 << 8);
static const int dx[] = {1, -1, 0, 0};
static const int dy[] = {0, 0, 1, -1};

int n, n2, m, k;
int d[N], r[N];
int a[N][N], c[N][N], w[N][N];
int f[N][N][S];
bool vis[N][N];
std::queue<pii> q;

FILE *fin, *fout, *ferr;
std::mt19937 gen(20060814);

void spfa(int s) {
	while (q.size()) {
		auto [x, y] = q.front();
		q.pop();
		vis[x][y] = false;
		for (int d = 0; d < 4; ++d) {
			int tx = x + dx[d], ty = y + dy[d];
			if (tx < 1 || tx > n || ty < 1 || ty > m)
				continue;
			if (c[tx][ty] == -1)
				continue;
			if (f[tx][ty][s] > f[x][y][s] + w[tx][ty]) {
				f[tx][ty][s] = f[x][y][s] + w[tx][ty];
				if (!vis[tx][ty])
					q.ep(tx, ty), vis[tx][ty] = true;
			}
		}
	}
}

int calc() {
	int ans = inf;
	int R = (1 << k) - 1;
	for (int t = 1; t <= 233; ++t)
	{	
		std::shuffle(d + 1, d + n2 + 1, gen);
		for (int i = 1; i <= n2; ++i)
			r[d[i]] = i % k;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				for (int s = 0; s <= R; ++s)
					f[i][j][s] = inf;
				if (~c[i][j])
					f[i][j][1 << r[c[i][j]]] = w[i][j];
			}
		for (int s = 1; s <= R; ++s) {
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= m; ++j)
					if (~c[i][j]) {
						for (int t = (s - 1) & s; t; t = (t - 1) & s)
							f[i][j][s] = std::min(f[i][j][s], f[i][j][t] + f[i][j][s ^ t] - w[i][j]);
						if (f[i][j][s] < 1000000000)
							q.ep(i, j), vis[i][j] = true;
					}
			spfa(s);
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				ans = std::min(ans, f[i][j][R]);
	}
	return ans;
}

void solve() {
	n2 = 0;
	fscanf(fin, "%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			fscanf(fin, "%d", c[i] + j), w[i][j] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			fscanf(fin, "%d", a[i] + j);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			d[++ n2] = c[i][j];

	std::sort(d + 1, d + n2 + 1);
	n2 = std::unique(d + 1, d + n2 + 1) - d - 1;
	int ans = calc();
	if (ans == inf)
		return fputs("-1 -1", fout), void();

	int l = 0, r = 1000000;
	while (l < r) {
		int mid = (l + r) >> 1;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				w[i][j] = ((a[i][j] <= mid) ? 9999 : 10001);	
		if (calc() <= ans * 10000)
			r = mid;
		else
			l = mid + 1;
	}
	return fprintf(fout, "%d %d\n", ans, l), void();
}

signed main() {
	fin = stdin;
	fout = stdout;
	ferr = stderr;
	int t;
	fscanf(fin, "%d", &t);
	while (t--) solve();
}