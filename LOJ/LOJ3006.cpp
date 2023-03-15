#include <bits/stdc++.h>

#define int long long

using PII = std::pair<int, int>;

FILE *fin, *fout, *ferr;

static const int N = 200'005;

int n, m, k, sum;
int a[N], l[N], r[N], id[N], ans[N];
int pre[N], nxt[N];
std::set<PII> s;
int calc(int x) { return std::abs(a[x] - a[nxt[x]]); }
void adds(int x)
{
    sum += calc(x);
    s.insert(PII(calc(x), x));
}
void dels(int x)
{
    sum -= calc(x);
    s.erase(PII(calc(x), x));
}
void del(int x)
{
    --k;
    if (pre[x])
        dels(pre[x]);
    if (nxt[x])
        dels(x);
    nxt[pre[x]] = nxt[x];
    pre[nxt[x]] = pre[x];
    if (pre[x] && nxt[x])
        adds(pre[x]);
}
void move(int x, int p)
{
    if (x < l[p])
    {
        ans[p] += l[p] - x;
        r[p] -= l[p] - x;
        l[p] = x;
    }
    if (x > r[p])
    {
        ans[p] += x - r[p];
        l[p] += x - r[p];
        r[p] = x;
    }
    return void();
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fscanf(fin, "%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%lld%lld", l + i, r + i);
    std::iota(id + 1, id + n + 1, 1);
    std::sort(id + 1, id + n + 1, [&](int a, int b)
              { return r[a] - l[a] < r[b] - l[b]; });
    for (int i = 1; i <= m; ++i)
    {
        static int x;
        fscanf(fin, "%lld", &x);
        if (x == a[k])
            continue;
        if (k > 1 && (a[k - 1] < a[k]) == (a[k] < x))
            --k;
        a[++k] = x;
    }
    pre[0] = k, nxt[0] = 1;
    pre[k] = k - 1, nxt[k] = 0;
    for (int i = 1; i < k; ++i)
        pre[i] = i - 1, nxt[i] = i + 1, adds(i);
    int i = 1;
    while (k > 2)
    {
        int x = s.begin()->second;
        while (i <= n && r[id[i]] - l[id[i]] < calc(x))
        {
            ans[id[i]] = sum - calc(nxt[0]) - (k - 2) * (r[id[i]] - l[id[i]]);
            move(a[nxt[0]], id[i]);
            move(a[nxt[nxt[0]]], id[i]);
            ++i;
        }
        if (pre[x])
            del(nxt[x]);
        if (nxt[x])
            del(x), x = pre[x];
        while (1)
        {
            int next = nxt[x];
            if (!x || !next)
                break;
            if (a[x] == a[next])
            {
                del(next);
                continue;
            }
            if ((pre[x]) && ((a[pre[x]] < a[x]) == (a[x] < a[next])))
            {
                del(x);
                continue;
            }
            if ((nxt[next]) && ((a[x] < a[next]) == (a[next] < a[nxt[next]])))
            {
                del(next);
                continue;
            }
            break;
        }
    }
    for (int j = i; j <= n; j++)
    {
        move(a[nxt[0]], id[j]);
        if (k > 1)
            move(a[nxt[nxt[0]]], id[j]);
    }
    for (int i = 1; i <= n; ++i)
        fprintf(fout, "%lld\n", ans[i]);
    return 0;
}