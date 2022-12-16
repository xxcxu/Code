#include <bits/stdc++.h>
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
static constexpr int P = 998244353;
int mat[7][37] = {
    {},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {-2, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {6, 499122171, 499122177, 0, 0, -499122182, -998244349, 0, 0, 0, 499122177, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {-23, -665496207, 499122170, 166374059, 0, -665496207, -32, -499122171, 0, 0, -499122183, 499122182, 0, 0, 0, 166374059, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {104, -748683419, 707089806, -249561093, 291154603, 249560934, 332748336, 499122106, 332748122, 0, 707089806, -499122247, -998244337, 0, 0, 748683260, 332748122, 0, 0, 0, -707089750, 0, 0, 0, 0}
};
int n, m, k, ans;
signed main() {
    freopen("tiles.in", "r", stdin);
    freopen("tiles.out", "w", stdout);
    read(n, m, k);
    for (int i = 0, x = 1; i <= 4; ++i, x = 1ll * x * n % P)
        for (int j = 0, y = 1; j <= 4; ++j, y = 1ll * y * m % P)
            ans = (ans + 1ll * mat[k][i * 5 + j] * x % P * y % P) % P;
    printf("%d\n", (ans + P) % P);
    return 0;
}