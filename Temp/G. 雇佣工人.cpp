#include <bits/stdc++.h>

#define int long long
#define fi first
#define se second
#define ep emplace

using pii = std::pair<int, int>;

static const int N = 500005;

FILE *fin, *fout, *ferr;
int n, w, ans;
pii a[N];

signed main()
{
    fin = stdin;
    fout = stdout;
    ferr = stderr;
    // fin = fopen("Input.txt", "r");
    // fout = fopen("Output.txt", "w+");
    // ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%lld%lld", &n, &w);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%lld%lld", &a[i].se, &a[i].fi);
    std::sort(a + 1, a + n + 1, [&](pii a, pii b)
              { return a.se * b.fi < a.fi * b.se; });
    int sum = 0, ans = 0;
    std::priority_queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        sum += a[i].fi;
        q.ep(a[i].fi);
        if ((int)q.size() && sum * a[i].se > w * a[i].fi)
            sum -= q.top(), q.pop();
        if (sum * a[i].se <= w * a[i].fi)
            ans = std::max(ans, (int)q.size());
    }
    fprintf(fout, "%lld\n", ans);
    return 0;
}