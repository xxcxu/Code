#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

#define eb emplace_back
#define all(x) x.begin(), x.end()

static const int N = 200'005;

int n, m;
int dp[N], from[N];
bool ban[N];
std::vector<int> ans, scc[N];

int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
int exgcd(int a, int b, int &x, int &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b, a % b, x, y);
	int tmp = x;
	x = y;
	y = tmp - y * (a / b);
	return d;
}

signed main()
{
	fin = stdin, fout = stdout, ferr = stderr;
	fscanf(fin, "%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		static int x;
		fscanf(fin, "%d", &x);
		ban[x] = true;
	}
	for (int i = 0; i < m; ++i)
	{
		if (ban[i])
			continue;
		scc[gcd(i, m)].eb(i);
	}
	if (ban[0])
		scc[m].eb(0);
	for (int i = 1; i <= m; ++i)
	{
		if (scc[i].empty())
			continue;
		for (int j = 1; j < i; ++j)
			if (i % j == 0)
			{
				if (dp[i] < dp[j])
					dp[i] = dp[j], from[i] = j;
			}
		dp[i] += (int)scc[i].size();
	}
	int id = m;
	while (scc[id].size())
	{
		for (auto x : scc[id])
			ans.eb(x);
		id = from[id];
	}
	std::reverse(all(ans));
	if (ban[0])
		ans.pop_back();
	fprintf(fout, "%d\n", (int)ans.size());
	int multi = 1;
	for (int i : ans)
	{
		static int x, y;
		int d = exgcd(multi, m, x, y);
		fprintf(fout, "%d ", ((1LL * x * i / d) % m + m) % m);
		multi = i;
	}
	return 0;
}