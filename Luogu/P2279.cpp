#include <bits/stdc++.h>
const int N = 1e3 + 5;
int n, f[N][5];
std::vector<int> Graph[N];
void Dfs(int x, int fa) {
    int sum2 = 0, sum3 = 0;
    if (!(Graph[x].size() - (x != 1))) return void(f[x][0] = f[x][1] = f[x][2] = 1);
    for (int y : Graph[x]) if (y ^ fa) {
        Dfs(y, x);
        sum2 += f[y][2], sum3 += f[y][3];
    }
    f[x][0] = 1, f[x][1] = f[x][2] = n + 1;
    for (int y : Graph[x]) if (y ^ fa) {
        f[x][0] += f[y][4];
        f[x][1] = std::min(f[x][1], f[y][0] + sum3 - f[y][3]);
        f[x][2] = std::min(f[x][2], f[y][1] + sum2 - f[y][2]);
        f[x][3] += f[y][2];
        f[x][4] += f[y][3];
    }
    for (int i = 1; i < 5; ++i) f[x][i] = std::min(f[x][i], f[x][i - 1]);
    return void();
}
signed main() {
    scanf("%d", &n);
    for (int i = 2, p; i <= n; ++i) {
        scanf("%d", &p);
        Graph[p].emplace_back(i);
        Graph[i].emplace_back(p);
    } Dfs(1, 0);
    return printf("%d\n", f[1][2]), 0;
}
