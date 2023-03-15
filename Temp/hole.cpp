#include <bits/stdc++.h>
#define int long long
#define all(x) x.begin(), x.end()
#define eb emplace_back
#define fi first
#define se second
FILE *fin, *fout, *ferr;
static const int N = 400'005, inf = 1e18;
int n, k;
int v, A, B, C;
int h[N], s[N], t[N];
struct line
{
    int k, b;
    line(int k = 0, int b = 0) : k(k), b(b) {}
    int operator()(const int &x) { return k * x + b; }
    line operator+(const line &a) { return line(this->k + a.k, this->b + a.b); }
    line operator-(const line &a) { return line(this->k - a.k, this->b - a.b); }
    bool operator<(line) { return false; }
};
using PIL = std::pair<int, line>;
std::vector<PIL> vec;
int check(int x)
{
    line L;
    vec.clear();
    int node1 = (x - 1) / 2;
    int node2 = (x + 1) / 2;
    for (int i = 1; i <= n; ++i)
    {
        int r = std::min(s[i], node1 + i);
        if (r >= 1)
        {
            L = L + line(-1, s[i]);
            vec.eb(r + 1, line(1, -s[i]));
        }
        int l = std::max(node2 + i, x + i - h[i]);
        vec.eb(l, line(1, t[i] - x));
    }
    vec.eb(1, line());
    std::sort(all(vec), [](PIL x, PIL y)
              { return x.fi < y.fi; });
    int ans = inf;
    for (int i = 0; i < (int)vec.size(); ++i)
    {
        auto [x, l] = vec[i];
        L = L + l;
        if (i == (int)vec.size() - 1)
            ans = std::min(ans, L(x));
        if (i < (int)vec.size() - 1 && vec[i + 1].fi != x)
            ans = std::min(ans, L(x));
    }
    return ans;
}
signed main()
{
    fin = fopen("hole.in", "r");
    fout = fopen("hole.out", "w+");
    ferr = stderr;
    fscanf(fin, "%lld%lld", &n, &k);
    fscanf(fin, "%lld%lld%lld%lld", &v, &A, &B, &C);
    h[1] = v;
    for (int i = 2; i <= n; ++i)
        h[i] = (1LL * h[i - 1] * A + B) % C + 1;
    for (int i = 1; i <= n; ++i)
        s[i] = h[i] + i, t[i] = h[i] - i;
    int p = std::max_element(s + 1, s + n + 1) - s;

    int l = n + 1, r = l;
    int height = h[p];
    h[p] = std::max(h[p] - k, 1LL);
    int max = -inf;
    for (int i = 1; i <= n; ++i)
    {
        r = std::max(r, h[i] + i + max);
        max = std::max(max, h[i] - i);
    }
    h[p] = height;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid) <= k)
            r = mid;
        else
            l = mid + 1;
    }
    return fprintf(fout, "%lld\n", l), 0;
}