#include <bits/stdc++.h>

using PII = std::pair<int, int>;

#define fi first
#define se second

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

static const int N = 500'005;

int n, m, cnt, lastans;
bool del[N * 2];
std::priority_queue<PII> heap[N << 2];

struct SGT
{
#define ls (x << 1)
#define rs (x << 1 | 1)
    void ins(int x, int l, int r, int ql, int qr, int v, int id)
    {
        if (ql <= l && r <= qr)
        {   
            heap[x].emplace(v, id);
            return void();
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            ins(ls, l, mid, ql, qr, v, id);
        if (qr > mid)
            ins(rs, mid + 1, r, ql, qr, v, id);
    }
    int ask(int x, int l, int r, int p)
    {
        while (heap[x].size() && del[heap[x].top().se])
            heap[x].pop();
        if (l == r)
            return ((int)heap[x].size() > 0) ? heap[x].top().fi : 0;
        int ans = ((int)heap[x].size() > 0) ? heap[x].top().fi : 0;
        int mid = (l + r) >> 1;
        return std::max(ans, p <= mid ? ask(ls, l, mid, p) : ask(rs, mid + 1, r, p));
    }
} tree;


signed main()
{
    freopen("threebody.in", "r", stdin);
    freopen("threebody.out", "w", stdout);
    int test_case;
    test_case = read();
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
    {
        static int l, r, x;
        l = read(), r = read(), x = read();
        tree.ins(1, 1, N - 5, l, r, x, i);
    }

    cnt = n;
    while (m--)
    {
        static int opt, l, r, x;
        opt = read();
        if (opt == 1)
        {
            l = read(), r = read(), x = read();
            l ^= lastans, r ^= lastans, x ^= lastans;
            tree.ins(1, 1, N - 5, l, r, x, ++cnt);
        }
        if (opt == 2)
        {
            x = read();
            x ^= lastans;
            del[x] = true;
        }
        if (opt == 3)
        {
            x = read();
            x ^= lastans;
            printf("%d\n", lastans = tree.ask(1, 1, N - 5, x));
        }
    }
    return 0;
}
/*
0
10 10
10 14 84
8 10 30
2 14 37
3 19 56
2 16 32
3 12 70
3 14 52
19 19 28
4 7 77
5 19 89
2 8
3 18
2 94
2 83
3 75
3 52
2 80
1 80 93 105
3 71
2 11
*/