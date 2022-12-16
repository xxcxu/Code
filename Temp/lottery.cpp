#include <bits/stdc++.h>
using ll = long long;
using pii = std::pair<int, int>;
static constexpr int N = 1e5 + 5, M1 = 1e2 + 5, M2 = 1e4 + 5, M3 = 1e6 + 5;
int n, a[N]; ll ans;
pii suf2[M1], suf4[M2], suf6[M3];
int mx[3][5], cnt[3];
std::map<int, int> map[3];
auto Check(int x, int y) -> bool {
    if (!~x || !~y) return false;
    return x % 100 == y % 100;
}
auto main() -> decltype(0) {
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) {
        ++ suf2[a[i] % 100].first;
        ++ suf4[a[i] % 10000].first;
        ++ suf6[a[i]].first;
    }
    for (int i = 0; i < 100; ++i) suf2[i].second = i;
    for (int i = 0; i < 10000; ++i) suf4[i].second = i;
    for (int i = 0; i < 1000000; ++i) suf6[i].second = i;
    std::memset(mx, -1, sizeof mx);
    std::sort(suf2, suf2 + 100);
    std::sort(suf4, suf4 + 10000);
    std::sort(suf6, suf6 + 1000000);
    for (int i = 99; ~i; --i) 
        if (!map[0].count(suf2[i].second % 100)) {
            map[0][suf2[i].second % 100] = true;
            mx[0][cnt[0] ++] = i;
            if (cnt[0] > 4) break;
        }
    for (int i = 9999; ~i; --i) 
        if (!map[1].count(suf4[i].second % 100)) {
            map[1][suf4[i].second % 100] = true;
            mx[1][cnt[1] ++] = i;
            if (cnt[1] > 4) break;
        }
    for (int i = 999999; ~i; --i) 
        if (!map[2].count(suf6[i].second % 100)) {
            map[2][suf6[i].second % 100] = true;
            mx[2][cnt[2] ++] = i;
            if (cnt[2] > 4) break;
        }
    for (int x = 0; x < 5; ++x)
    for (int y = 0; y < 5; ++y)
    for (int z1 = 0; z1 < 5; ++z1)
    for (int z2 = z1 + 1; z2 < 5; ++z2)
    for (int z3 = z2 + 1; z3 < 5; ++ z3) {
        int fx = ~mx[2][x] ? suf6[mx[2][x]].second : -1;
        int fy = ~mx[1][y] ? suf4[mx[1][y]].second : -1;
        int fz1 = ~mx[0][z1] ? suf2[mx[0][z1]].second : -1;
        int fz2 = ~mx[0][z2] ? suf2[mx[0][z2]].second : -1; 
        int fz3 = ~mx[0][z3] ? suf2[mx[0][z3]].second : -1;
        if (Check(fx, fy) || Check(fx, fz1)) continue;
        if (Check(fx, fz2) || Check(fx, fz3)) continue;
        if (Check(fy, fz1) || Check(fy, fz2) || Check(fy, fz3)) continue;
        long long ret = 0;
        ret += ~fx ? suf6[mx[2][x]].first * 300000ll : 0;
        ret += ~fy ? suf4[mx[1][y]].first * 4000ll : 0;
        ret += ~fz1 ? suf2[mx[0][z1]].first * 500ll : 0;
        ret += ~fz2 ? suf2[mx[0][z2]].first * 500ll : 0;
        ret += ~fz3 ? suf2[mx[0][z3]].first * 500ll : 0;
        ans = std::max(ret, ans);
    }
    return printf("%lld\n", ans), 0;
}