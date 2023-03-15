#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;
using LD = long double;
static const int N = 15, S = 1 << 15;
static const LD eps = 1e-8;
int n, m, k;
int a[N], sum[S], cnt[N][2];
LD p[N][2], dp[S][2];

LD check0(int S, LD v)
{
	LD ans = 0.0;
	for (int i = 0; i < n; i++)
		if ((S >> i & 1) && (p[i][0]))
			ans += std::max((LD)0, p[i][0] * (a[i] + dp[S ^ (1 << i)][1] - v));
	return ans + v;
}
LD check1(int S, LD v)
{
	LD ans = 0.0;
	for (int i = 0; i < n; i++)
		if ((S >> i & 1) && (p[i][1]))
			ans += std::min((LD)0, p[i][1] * (a[i] + dp[S ^ (1 << i)][0] - v));
	return ans + v;
}

int count(int x)
{
	int res = 0;
	for (; x; x -= x & -x)
		++res;
	return res;
}

signed main()
{
	fin = stdin, fout = stdout, ferr = stderr;
	fin = fopen("card.in", "r");
	fout = fopen("card.out", "w+");
	fscanf(fin, "%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; ++i)
		fscanf(fin, "%d", a + i);
	std::sort(a, a + n);
	for (int S = 0; S < (1 << n); ++S)
		for (int i = 0; i < n; ++i)
			if (S >> i & 1)
				sum[S] += a[i];
	int R = (1 << n) - 1;
	for (int S = 0; S < (1 << n); ++S)
	{
		int ls = count(S);
		if (ls <= k)
		{
			dp[S][0] = dp[S][1] = 0;
			continue;
		}
		int tot = 0;
		std::memset(cnt, 0, sizeof cnt);
		for (int T = S; T; T = (T - 1) & S)
		{
			int lt = count(T);
			if (lt > m || (lt < m && lt < ls))
				continue;
			++tot;
			for (int i = n - 1; i >= 0; --i)
				if (T >> i & 1)
				{
					++cnt[i][0];
					break;
				}
			for (int i = 0; i < n; ++i)
				if (T >> i & 1)
				{
					++cnt[i][1];
					break;
				}
		}
		for (int i = 0; i < n; ++i)
		{
			p[i][0] = S >> i & 1 ? 1.0 * cnt[i][0] / tot : 0;
			p[i][1] = S >> i & 1 ? 1.0 * cnt[i][1] / tot : 0;
		}
		LD l = 0, r = sum[R];
		while (r - l >= eps)
		{
			LD mid = (l + r) / 2.0;
			if (check0(S, check1(S, mid)) < mid)
				r = mid;
			else
				l = mid;
		}
		dp[S][0] = (l + r) / 2.0;
		dp[S][1] = check1(S, dp[S][0]);
	}
	return fprintf(fout, "%.7Lf\n", dp[R][0]), 0;
}