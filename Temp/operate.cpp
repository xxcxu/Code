#include <bits/stdc++.h>

using PII = std::pair<int, int>;

FILE *fin, *fout, *ferr;

std::unordered_map<int, int> map;
std::map<PII, int> ans;

static const int N = 25;

std::vector<int> p;
int cnt, q[N];

void init(int n)
{
    std::memset(q, 0, sizeof q);
    cnt = 0;
    p.clear();
    p.emplace_back(0);
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
            p.emplace_back(i), ++cnt;
        while (n % i == 0)
        {
            ++q[cnt];
            n /= i;
        }
    }
    if (n != 1)
        p.emplace_back(n), ++q[++cnt];
    return void();
}

int dis(int a, int b) { return std::abs(b - a); }

int dfs(int a, int b)
{
    if (a == 1)
        return 0;
    if (ans.count(PII(a, b)))
        return ans[PII(a, b)];
    int res = dis(a, 1);
    for (int i = 1; i <= cnt; ++i)
    {
        int P = p[i];
        if (q[i] == 0)
            continue;
        if (a % P == 0)
        {
            --q[i];
            res = std::min(res, dfs(a / P, b / P) + 1);
            ++q[i];
            continue;
        }
        int le = a / P * P, ri = (a / P + 1) * P;
        --q[i];
        if (le && dis(le, a) + 1 < res)
            res = std::min(res, dfs(le / P, (b - (a - le)) / P) + 1 + dis(le, a));
        if (ri && dis(ri, a) + 1 < res)
            res = std::min(res, dfs(ri / P, (b + (ri - a)) / P) + 1 + dis(ri, a));
        ++q[i];
    }
    return ans[PII(a, b)] = res;
}

void solve()
{
    static int a, b;
    fscanf(fin, "%d%d", &a, &b);
    if (a > b)
        std::swap(a, b);
    init(b - a);
    fprintf(fout, "%d\n", dfs(a, b));
}

signed main()
{
    fin = fopen("operate.in", "r");
    fout = fopen("operate.out", "w+");
    int t;
    fscanf(fin, "%d", &t);
    while (t--)
        solve();
    return 0;
}