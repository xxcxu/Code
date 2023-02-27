#include <bits/stdc++.h>

#define int long long

static const int N = 500005, inf = 1000000000000000000;

int n, U, D, S, f[N], L[N], R[N];
FILE *fin, *fout, *ferr;

struct Node
{
    int T, L, W;
    void read() { fscanf(fin, "%lld%lld%lld", &T, &L, &W); }
    bool operator<(const Node &a)
    {
        return std::tie(T, L) < std::tie(a.T, a.L);
    }
} a[N];

class LB
{
public:
    int lowbit(int x) { return x & -x; }
};
class TreeArray1 : public LB
{
public:
    TreeArray1() { std::memset(s, -0x3f, sizeof s); }
    void add(int x, int v)
    {
        for (; x < N; x += lowbit(x))
            s[x] = std::max(s[x], v);
        return void();
    }
    int ask(int x)
    {
        int ans = -inf;
        for (; x >= 1; x -= lowbit(x))
            ans = std::max(ans, s[x]);
        return ans;
    }

private:
    int s[N];
} t1;
class TreeArray2 : public LB
{
public:
    TreeArray2() { std::memset(s, -0x3f, sizeof s); }
    void add(int x, int v)
    {
        for (; x >= 1; x -= lowbit(x))
            s[x] = std::max(s[x], v);
        return void();
    }
    int ask(int x)
    {
        int ans = -inf;
        for (; x < N; x += lowbit(x))
            ans = std::max(ans, s[x]);
        return ans;
    }

private:
    int s[N];
} t2;

void solve(int l, int r)
{
    for (int i = l; i <= r; ++i)
    {
        L[i] = R[i] = std::max(t1.ask(a[i].L) - a[i].L * U, t2.ask(a[i].L) + a[i].L * D) + a[i].W;
    }
    for (int i = l + 1; i <= r; ++i)
        L[i] = std::max(L[i], L[i - 1] - (a[i].L - a[i - 1].L) * U + a[i].W);
    for (int i = r - 1; i >= l; --i)
        R[i] = std::max(R[i], R[i + 1] - (a[i + 1].L - a[i].L) * D + a[i].W);
    for (int i = l; i <= r; ++i)
    {
        f[i] = std::max(L[i], R[i]);
        t1.add(a[i].L, f[i] + a[i].L * U);
        t2.add(a[i].L, f[i] - a[i].L * D);
    }
}

signed main()
{
    fin = stdin;
    fout = stdout;
    ferr = stderr;
    // fin = fopen("Input.txt", "r");
    // fout = fopen("Output.txt", "w+");
    // ferr = fopen("Debug.txt", "w+");
    std::memset(f, -0x3f, sizeof f);
    fscanf(fin, "%lld%lld%lld%lld", &n, &U, &D, &S);
    for (int i = 1; i <= n; ++i)
        a[i].read();
    a[0] = {0, S, 0};
    a[++n] = {1000000000, S, 0};
    std::sort(a + 1, a + n + 1);
    t1.add(S, S * U);
    t2.add(S, -S * D);
    for (int i = 1; i <= n; ++i)
    {
        int l = i, r = i;
        while (a[l].T == a[r + 1].T)
            ++r;
        solve(l, r);
        i = r;
    }
    return fprintf(fout, "%lld\n", f[n]), 0;
}