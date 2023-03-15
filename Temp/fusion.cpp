#include <bits/stdc++.h>

#define For(i, a, b) for (int i = a, i##end = b; i <= i##end; ++i)
#define rFor(i, b, a) for (int i = b, i##end = a; i >= i##end; --i)

typedef long long ll;
typedef std::pair<int, int> pii;
#define fi first
#define se second

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
T myrand(T l, T r)
{
    return std::uniform_int_distribution<T>(l, r)(rnd);
}

template <typename T, typename... Args>
void LOG(T x, Args... args)
{
#ifdef DEBUG
    fprintf(stderr, x, args...);
#endif
}

const int kW = 505;
const int kN = 250005;
const int kK = 1e4 + 5;

int W, H, n, k, minx = 1e9, miny = 1e9, maxx, maxy, x[kN], y[kN], X[kK], Y[kK];
std::bitset<kW> no[kW], d[kW], ban[kW];

int main()
{
    freopen("fusion.in", "r", stdin);
    freopen("fusion.out", "w", stdout);
    scanf("%d%d%d", &W, &H, &n);
    For(i, 1, n) scanf("%d%d", x + i, y + i), ban[x[i]][y[i]] = 1;
    scanf("%d", &k);
    For(i, 1, k)
    {
        scanf("%d%d", X + i, Y + i);
        minx = std::min(minx, X[i]);
        miny = std::min(miny, Y[i]);
    }
    For(i, 1, k)
    {
        X[i] -= minx, Y[i] -= miny;
        maxx = std::max(maxx, X[i]), maxy = std::max(maxy, Y[i]);
        if (X[i] > W)
        {
            printf("0");
            return 0;
        }
        if (Y[i] > H)
        {
            printf("0");
            return 0;
        }
    }
    For(i, 1, k)
    {
        int nxt = i == k ? 1 : i + 1;
        int u = Y[i] < Y[nxt] ? i : nxt, v = i ^ nxt ^ u;
        For(y, Y[u], Y[v] - 1)
        {
            int x = X[u] < X[v] ? X[u] + ((y - Y[u]) * (X[v] - X[u]) + Y[v] - Y[u] - 1) / (Y[v] - Y[u]) : X[v] + ((Y[v] - y) * (X[u] - X[v]) + Y[v] - Y[u] - 1) / (Y[v] - Y[u]);
            d[x][y] = !d[x][y];
        }
    }
    For(x, 1, W) For(y, 0, H) d[x][y] = d[x][y] != d[x - 1][y];
    For(i, 1, k)
    {
        int nxt = i == k ? 1 : i + 1, u, v;
        u = Y[i] < Y[nxt] ? i : nxt, v = i ^ nxt ^ u;
        int g = std::__gcd(Y[v] - Y[u], std::abs(X[u] - X[v]));
        for (int x = X[u], y = Y[u];; x += (X[v] - X[u]) / g, y += (Y[v] - Y[u]) / g)
        {
            d[x][y] = 1;
            if (x == X[v] && y == Y[v])
                break;
        }
    }
    For(i, 0, maxx) For(j, 0, maxy) if (d[i][j])
    {
        For(k, i, W) no[k - i] |= ban[k] >> j;
    }  
    int ans = 0;
    For(i, 0, W - maxx) For(j, 0, H - maxy) if (!no[i][j])++ ans;
    printf("%d", ans);
    return 0;
}