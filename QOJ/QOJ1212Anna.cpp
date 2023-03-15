#include <bits/stdc++.h>
#include "Annalib.h"

#define eb emplace_back
static const int N = 1'000'005;

int col[N];
std::vector<int> e[N];

void dfs(int x, int fa)
{
    for (int y : e[x])
        if (y != fa)
        {
            col[y] = col[x] ^ (y >= x);
            dfs(y, x);
        }
}
void Anna(int K, int N, int T, int A[], int B[])
{
    for (int i = 0; i < N - 1; ++i)
    {
        e[A[i]].eb(B[i]);
        e[B[i]].eb(A[i]);
    }
    dfs(T, -1);
    for (int i = 1; i <= N; ++i)
        Flag(i, col[i]);
    return void();
}