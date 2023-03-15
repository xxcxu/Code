#include <bits/stdc++.h>
FILE *fin, *fout, *ferr;
using TII = std::tuple<int, int>;
static const int N = 7'505;
int n, a[N], sum[N], pre[N], nxt[N], len[N][N];
long long ans;
std::vector<int> vec1[N * 2], vec2[N * 2];
char s[N];
struct TreeArray
{
	int n;
	int s1[N * 2], s2[N * 2];
	int lowbit(int x) { return x & -x; }
	void add(int x, int v1, int v2)
	{
		for (; x <= this->n; x += lowbit(x))
			s1[x] += v1, s2[x] += v2;
		return void();
	}
	TII ask(int x)
	{
		int ans1 = 0, ans2 = 0;
		for (; x >= 1; x -= lowbit(x))
			ans1 += s1[x], ans2 += s2[x];
		return std::tie(ans1, ans2);
	}
	void clear()
	{
		std::memset(s1, 0, (this->n + 1) * sizeof(int));
		std::memset(s2, 0, (this->n + 1) * sizeof(int));
	}
} tree1, tree2;

signed main()
{
	fin = stdin, fout = stdout, ferr = stderr;
	// fin = fopen("Input.txt", "r");
	// fout = fopen("Output.txt", "w+");
	// ferr = fopen("Debug.txt", "w+");
	fscanf(fin, "%s", s + 1);
	n = std::strlen(s + 1);
	tree1.n = tree2.n = 2 * n;
	pre[0] = 0, nxt[n + 1] = n + 1;
	for (int i = 1; i <= n; ++i)
		a[i] = s[i] == 'G';
	for (int i = 1; i <= n; ++i)
		sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i <= n; ++i)
		pre[i] = a[i] ? i : pre[i - 1];
	for (int i = n; i >= 1; --i)
		nxt[i] = a[i] ? i : nxt[i + 1];
	for (int l = 1; l <= n; ++l)
		for (int r = l; r <= n; ++r)
		{
			int i = nxt[l], j = pre[r];
			if (i > j)
				continue;
			if ((r - l) % 2 == 1)
				if ((sum[j] - sum[i]) % 2 == 0)
					--ans;
		}
	for (int p = nxt[1]; nxt[p + 1]; p = nxt[p + 1])
	{
		for (int i = 1; i <= n * 2; ++i)
			vec1[i].clear(), vec2[i].clear();
		tree1.clear(), tree2.clear();
		for (int i = 1, j = p, k = nxt[p + 1]; 1 <= j && k <= n; ++i, j = pre[j - 1], k = nxt[k + 1])
		{
			vec2[j + k].push_back(i);
			tree1.add(i, 1, j + k);
			for (int l = j; l > pre[j - 1]; --l)
				for (int r = k; r < nxt[k + 1]; ++r)
					vec1[l + r].push_back(l), len[l][r] = i;
		}
		for (int i = 1; i <= n * 2; ++i)
		{
			for (int j : vec2[i])
			{
				tree1.add(j, -1, -i);
				tree2.add(j, 1, i);
			}
			for (int l : vec1[i])
			{
				int r = i - l;
				auto [b1, a1] = tree1.ask(len[l][r]);
				auto [b2, a2] = tree2.ask(len[l][r]);
				ans += (a1 - a2) + (b2 - b1) * i;
			}
		}
	}
	for (int p = nxt[1]; p <= n; p = nxt[p + 1])
	{
		for (int i = 1; i <= n * 2; i++)
			vec1[i].clear(), vec2[i].clear();
		tree1.clear(), tree2.clear();
		for (int i = 0, j = p, k = p; 1 <= j && k <= n; ++i, j = pre[j - 1], k = nxt[k + 1])
		{
			if (i)
			{
				vec2[j + k].push_back(i);
				tree1.add(i, 1, j + k);
			}
			for (int l = j; l > pre[j - 1]; --l)
				for (int r = k; r < nxt[k + 1]; ++r)
					if ((l + r) % 2 == 0)
						vec1[l + r].push_back(l), len[l][r] = i;
		}
		for (int i = 1; i <= n * 2; ++i)
		{
			for (int j : vec2[i])
			{
				tree1.add(j, -1, -i);
				tree2.add(j, 1, i);
			}
			for (int l : vec1[i])
			{
				int r = i - l;
				auto [b1, a1] = tree1.ask(len[l][r]);
				auto [b2, a2] = tree2.ask(len[l][r]);
				ans += (a1 - a2) + (b2 - b1) * i + std::abs(i / 2 - p);
			}
		}
	}
	return fprintf(fout, "%lld\n", ans), 0;
}