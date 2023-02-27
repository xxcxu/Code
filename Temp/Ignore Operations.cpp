#include <bits/stdc++.h>

#define int long long

using pii = std::pair<int, int>;

#define eb emplace_back

FILE *fin, *fout, *ferr;

static const int N = 200'005, inf = 0x3f3f3f3f3f3f3f;

int n, k;
int t[N], y[N], sum[N];
std::priority_queue<int> q;

int ask(int l, int r)
{
    return sum[r] - sum[l - 1];
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%lld%lld", &n, &k);
    for (int i = 1; i <= n; ++i)
        fscanf(fin, "%lld%lld", t + i, y + i);
    t[0] = 1, y[0] = 0;

    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + bool(t[i] == 2) * y[i];

    int ans = -inf, cnt = 0, sum = 0;
    for (int i = n; i >= 0; --i)
    {
        if (cnt > k)
            break;
        if (t[i] == 1)
        {
            ans = std::max(ans, y[i] + ask(i + 1, n) - sum);
            if ((int)q.size() == k - cnt)
            {
                sum -= q.top();
                q.pop();
            }
            ++cnt;
        }
        if (t[i] == 2)
        {
            if (y[i] >= 0)
                continue;
            q.emplace(y[i]);
            sum += y[i];
            if ((int)q.size() > k - cnt)
            {
                sum -= q.top();
                q.pop();
            }
        }
    }
    fprintf(fout, "%lld\n", ans);
    return 0;
}