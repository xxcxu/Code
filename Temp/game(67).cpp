#include <bits/stdc++.h>
#include "game.h"

static const int N = 5'000'005;

int n;
int b[N];
struct SGT
{
#define ls (x << 1)
#define rs (x << 1 | 1)
    int tr[N << 2];
    void pushup(int x)
    {
        tr[x] = tr[ls] + tr[rs];
        return void();
    }
    void build(int x, int l, int r)
    {
        if (l == r)
        {
            tr[x] = 2 * (int)std::log2(b[l]) + 3;
            return void();
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pushup(x);
    }
    void modify(int x, int l, int r, int p, int v)
    {
        if (l == r)
        {
            tr[x] = 2 * (int)std::log2(b[l] = v) + 3;
            return void();
        }
        int mid = (l + r) >> 1;
        p <= mid ? modify(ls, l, mid, p, v) : modify(rs, mid + 1, r, p, v);
        pushup(x);
    }
    int query(int x, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return tr[x];
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid)
            ans += query(ls, l, mid, ql, qr);
        if (qr > mid)
            ans += query(rs, mid + 1, r, ql, qr);
        return ans;
    }
} SGT;

void build(std::vector<long long> a, bool flag)
{
    n = (int)a.size() - 1;
    for (int i = 1; i <= n; ++i)
        b[i] = a[i];
    SGT.build(1, 1, n);
}
void modify(int p, long long x)
{
    SGT.modify(1, 1, n, p, x);
}
int query(int l, int r)
{
    return SGT.query(1, 1, n, l, r);
}