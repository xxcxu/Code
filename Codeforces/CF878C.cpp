#include <bits/stdc++.h>
static constexpr int N = 20;
int n, k;
struct node {
    int size;
    int max[N], min[N];
    node(): size(0) {
        std::memset(max, 0, sizeof max);
        std::memset(min, 0x3f, sizeof min);
    }
    friend bool operator < (node a, node b) {
        for (int i = 1; i <= k; ++i)
            if (a.max[i] > b.min[i]) return false;
        return true;
    }
    auto Merge(node a) -> void {
        size = size + a.size;
        for (int i = 1; i <= k; ++i) {
            max[i] = std::max(max[i], a.max[i]);
            min[i] = std::min(min[i], a.min[i]);
        }
    }
};
std::set<node> s;
auto main() -> decltype(0) {
    scanf("%d%d", &n, &k);
    node game;
    for (int i = 1; i <= n; ++i) {
        game.size = 1;
        for (int j = 1; j <= k; ++j) {
            scanf("%d", &game.min[j]);
            game.max[j] = game.min[j];
        }
        std::set<node>::iterator it;
        while ((it = s.find(game)) != s.end()) {
            game.Merge(*it);
            s.erase(it);
        } s.insert(game);
        printf("%d\n", s.rbegin() -> size);
    } return 0;
}