# include <bits/stdc++.h>
 
static const int N = 20;

int n, nn, m, dout[N], e[N][N];
int ans[N];
int f[1 << N], g[1 << N]; 

int Dp(int S) {
    if (!g[S]) {
        for (int i = 1; i <= n; ++i)
            if (S >> i & 1) ans[i] = 1;
        return 1;
    }
    int T = S ^ g[S], v = Dp(g[S]) + 1;
    for (int i = 1; i <= n; ++i)
        if (T >> i & 1) ans[i] = v;
    return v;
}

signed main() {
	scanf("%d%d", &n, &m); nn = n + 1;
	for (int i = 1; i <= m; i++) {
        static int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
		e[u][v] = w;
        dout[u] |= (1 << v);
    }
	std::memset(f, 63, sizeof f); f[0] = 0;

    int p = 0;
    for (int i = 1; i <= n; ++i) if (!dout[i]) p = 1 << i;
    f[p] = 0;

    for (int S = 0; S < (1 << nn); S += 2) {
        if (f[S] < 1000000000) {
            int T = 0;
            for (int i = 1; i <= n; ++i)
                if ((S & dout[i]) == dout[i]) T |= 1 << i;
            T &= (1 << nn) - S - 2;
            for (int i = 1; i <= n; ++i) if (S >> i & 1)
                for (int j = 1; j <= n; ++j) if (!(S >> j & 1))
                    f[S] += e[j][i];
            for (int s = T; s; s = (s - 1) & T)
                if (f[S] <= f[S | s])
                    f[S | s] = f[S], g[S | s] = S;
        }
    }    

    Dp((1 << nn) - 2);
    
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}