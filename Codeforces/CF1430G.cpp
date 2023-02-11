#include <cstdio>
 
#include <vector>
 
#include <cstring>
 
using namespace std;
 
struct Edge { int to, vl; }; int G[20][20]; int n, m, G0[20], G1[20], f[1 << 20];
 
int ans[20], fr[1 << 20];
 
int dfs(int S)
{
	if (fr[S] == 0)
	{
		for (int i = 1; i <= n; i++) if (S & (1 << i)) ans[i] = 1; return 1;
	}
	int nS = fr[S] ^ S, dp = dfs(fr[S]) + 1;
	for (int i = 1; i <= n; i++) if (nS & (1 << i)) ans[i] = dp; return dp;
}
 
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v, w; i <= m; i++) scanf("%d%d%d", &u, &v, &w),
		G[u][v] = w, G0[u] |= (1 << v), G1[v] |= (1 << u);
	memset(f, 63, sizeof f); f[0] = 0; int ps = 0;
	for (int i = 1; i <= n; i++) if (!G0[i]) ps = (1 << i);
	for (int S = ps; S; S = (S - 1) & ps) f[S] = 0;
	for (int S = 0; S < (1 << n + 1); S += 2) if (f[S] < 1e9)
	{
		int nS = 0; for (int i = 1; i <= n; i++) if ((G0[i] & S) == G0[i]) nS |= 1 << i;
		nS = nS & ((1 << n + 1) - 2 - S);
		for (int u = 1; u <= n; u++) if (S & (1 << u))
			for (int v = 1; v <= n; v++) if (!(S & (1 << v))) f[S] += G[v][u];
		for (int s = nS; s; s = (s - 1) & nS) if (f[S] <= f[s ^ S]) f[s ^ S] = f[S], fr[s ^ S] = S;
	}
	//printf("%d\n", f[(1 << n + 1) - 2]); return 0;
	dfs((1 << n + 1) - 2); for (int i = 1; i <= n; i++) printf("%d ", ans[i]); return 0;
}