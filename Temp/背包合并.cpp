#include <bits/stdc++.h>
#define int __int128
static const int N = 605;
int read()
{
    int t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar())
        t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}

void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

int n, V, i, j, p, S, Y, C, x, w[N], dp[N * N];

signed main()
{
    n = read(), S = read(), Y = read(), C = read();
    for (int i = 1; i <= n; ++i)
    {
        static int wi, vi;
        wi = read();
        vi = read();
        w[vi] = std::max(w[vi], wi);
        V = std::max(V, vi);
    }
    p = V;
    for (int i = 0; i < V; ++i)
        if (w[i] * p > w[p] * i)
            p = i;
    n = p * V;

    for (int i = 1; i <= V; ++i)
        for (int j = i; j <= n; ++j)
            dp[j] = std::max(dp[j - i] + w[i], dp[j]);
    for (int i = 1; i <= p; ++i)
    {
        int x = (i * Y - n) / p + 1;
        if (i * Y < n)
            w[i] = dp[i * Y];
        else
            w[i] = dp[i * Y - x * p] + x * w[p];
        w[i] = w[i] - (i - 1) * C;
    }
    V = p;

    for (int i = 0; i < V; ++i)
        if (w[i] * p > w[p] * i)
            p = i;
    for (int i = 0; i < N * N; ++i)
        dp[i] = 0;
    int x = (S - p * V) / p + 1;
    n = S - x * p;

    for (int i = 1; i <= V; ++i)
        for (int j = i; j <= n; ++j)
            dp[j] = std::max(dp[j], dp[j - i] + w[i]);
    write(dp[n] + x * w[p]);
    puts("");
    return 0;
}