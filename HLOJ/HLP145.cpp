#include <bits/stdc++.h>
#define fi first
#define se second
#define int long long
using namespace std;
#define pb push_back
#define mkp make_pair
#define ll long long
const int N = 1e5 + 5, mod = 577, inf = 1e17;
const ll lim = 1e11;
int n, a[N], f[N], g[N], dp[N];
queue<ll> que;
vector<pair<ll, int>> use[N];
struct Hash_Table
{
	int tot;
	int h[mod + 10], nxt[mod + 10], v2[mod + 10];
	ll v1[mod + 10];
	int H(ll &x) { return x % mod; }
	void clear()
	{
		tot = 0;
		memset(h, 0, sizeof(h));
	}
	int find(ll x)
	{
		const int hx = H(x);
		for (int i = h[hx]; i; i = nxt[i])
			if (v1[i] == x)
				return i;
		return 0;
	}
	void add(ll x, int y)
	{
		int t = find(x);
		if (!t)
		{
			const int hx = H(x);
			nxt[++tot] = h[hx];
			h[hx] = tot;
			v1[tot] = x;
			v2[tot] = 0;
			t = tot;
		}
		v2[t] = y;
	}
	int ask(ll x)
	{
		int t = find(x);
		if (t)
			return v2[t];
		return 0;
	}
} dis;
void bfs(int id)
{
	dis.clear();
	que.push(a[id]);
	dis.add(a[id], 0);
	while (!que.empty())
	{
		ll u = que.front();
		int d = dis.ask(u);
		use[id].pb(mkp(u, d));
		que.pop();
		if (u > lim)
			continue;
		ll v = u * 2;
		if (!dis.find(v))
		{
			dis.add(v, d + 1);
			que.push(v);
		}
		v = u / 2;
		if (v && !dis.find(v))
		{
			dis.add(v, d + 1);
			que.push(v);
		}
	}
	sort(use[id].begin(), use[id].end());
}
signed main()
{
	//	freopen("test.in","r",stdin);
	//	freopen("test.out","w",stdout);
	int T;
	scanf("%lld", &T);
	while (T--)
	{
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		for (int i = 1; i <= n; i++)
			use[i].clear();
		int ans = inf;
		for (int i = n; i >= 1; i--)
		{
			bfs(i);
			if (i + 2 <= n)
				vector<pair<ll, int>>().swap(use[i + 2]);
			if (i == n)
			{
				for (int j = 0; j < use[i].size(); j++)
					f[j] = use[i][j].second;
				continue;
			}
			int mn = inf;
			for (int j = use[i + 1].size() - 1, k = use[i].size() - 1; k >= 0; k--)
			{
				while (j >= 0 && use[i + 1][j].first >= use[i][k].first)
					mn = min(mn, f[j--]);
				g[k] = mn + use[i][k].second;
			}
			for (int j = 0; j < use[i].size(); j++)
				f[j] = g[j];
			int s = use[i].size(), v = inf;
			for (int j = 0; j < use[i].size(); j++)
				if (use[i][j].first * 2 > lim)
					v = min(v, f[j] + n - (i - 1));
			use[i].push_back(mkp(lim + 1, v));
			f[s] = v;
		}
		for (int i = 0; i < use[1].size(); i++)
			ans = min(ans, f[i]);
		printf("%lld\n", ans);
	}
}