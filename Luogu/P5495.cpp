#include <bits/stdc++.h>
static constexpr int N = 2e7 + 5;
uint32_t n, seed, ans, a[N];
bool vis[N];
auto Builder(uint32_t &seed) -> void {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
}
auto main() -> decltype(0) {
    scanf("%u%u", &n, &seed);
    for (int i = 1; i <= n; ++i) Builder(seed), a[i] = seed;
    vis[1] = true;
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) {
            vis[i] = true;
            for (int j = 1; i * j <= n; ++j)
                a[i * j] += a[j], vis[i * j] = true;
        }
    for (int i = 1; i <= n; ++i) ans ^= a[i];
    return printf("%u\n", ans), 0;
}