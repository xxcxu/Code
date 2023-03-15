#include <bits/stdc++.h>

static const int N = 200'005, M = 200'000, P = 998'244'353;

#define eb emplace_back
#define all(x) x.begin(), x.end()

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

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }
template <typename... Args>
int mul(int x, Args... args) { return mul(x, mul(args...)); }
int qpow(int x, int y)
{
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1)
            ans = mul(ans, x);
    return ans;
}
int inv(int x) { return qpow(x, P - 2); }

int d[N];
int bel[N], ans[N];
struct query
{
    int l, r, id;
    query(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id) {}
};
std::vector<query> ask;

int fac[N], ifac[N], invi[N];
void init(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = mul(fac[i - 1], i);
    ifac[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; --i)
        ifac[i] = mul(ifac[i + 1], i + 1);
    invi[0] = invi[1] = 1;
    for (int i = 2; i <= n; ++i)
        invi[i] = mul(P - P / i, invi[P % i]);
    return void();
}
int binom(int n, int m)
{
    if (n < m || m < 0)
        return 0;
    return mul(fac[n], ifac[m], ifac[n - m]);
}

struct Value
{
    int l, r;
    int sum1, sum2;
    Value(int l = 0, int r = 0, int sum1 = 0, int sum2 = 1) : l(l), r(r), sum1(sum1), sum2(sum2) {}
    void addl()
    {
        int tmp = sum2;
        sum2 = inc(sum2, mul(dec(sum1, mul(r, sum2)), invi[r - l]));
        sum1 = inc(sum1, tmp);
        ++l;
    }
    void addr()
    {
        int tmp = sum1;
        sum1 = inc(mul(inc(r, 1), sum1), mul(inc(dec(r, l), 1), sum2));
        sum2 = tmp;
        ++r;
    }
    void dell()
    {
        int tmp = mul(inc(mul(dec(l, 1), sum1), mul(inc(dec(r, l), 1), sum2)), invi[l]);
        sum2 = dec(sum1, tmp);
        sum1 = tmp;
        --l;
    }
    void delr()
    {
        int tmp = sum2;
        sum2 = mul(dec(sum1, mul(r, sum2)), invi[r - l]);
        sum1 = tmp;
        --r;
    }
};

signed main()
{
    freopen("qwq.in", "r", stdin);
    freopen("qwq.out", "w", stdout);
    init(M);
    int B = std::sqrt(M);
    d[0] = 1, d[1] = 0, d[2] = 1;
    for (int i = 3; i <= M; ++i)
        d[i] = mul(i - 1, inc(d[i - 1], d[i - 2]));
    for (int i = 1; i <= M; ++i)
        bel[i] = (i - 1) / B + 1;
    int q = read();
    for (int i = 1; i <= q; ++i)
    {
        static int n, m;
        n = read(), m = read();
        if (m == 0)
            ans[i] = d[n];
        else if (m > n - m)
            ans[i] = 0;
        else
            ask.eb(m, n - m, i);
    }
    std::sort(all(ask), [&](const query &a, const query &b)
              { return bel[a.l] == bel[b.l] ? a.r < b.r : a.l < b.l; });

    Value now = Value(0, 0, 0, 1);
    for (auto [l, r, id] : ask)
    {
        while (now.r < r)
            now.addr();
        while (now.l > l)
            now.dell();
        while (now.r > r)
            now.delr();
        while (now.l < l)
            now.addl();
        ans[id] = mul(now.sum2, binom(r, l), fac[l]);
    }
    for (int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}