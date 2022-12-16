#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 2e5 + 5;
int n, rt, ans, dep[N];
std::vector<int> Graph[N];
std::map<pii, int> map;
void Dfs(int x, int fa) {for (int y : Graph[x]) if (y ^ fa) dep[y] = dep[x] + 1, Dfs(y, x);}
signed main() {
    std::function<void(int, int)> add = [&](int a, int b) {Graph[a].emplace_back(b); Graph[b].emplace_back(a);};
    scanf("%d", &n);
    for (int i = 1, a[3]; i <= n - 2; ++i) {
        scanf("%d%d%d", &a[0], &a[1], &a[2]);
    	std::sort(a, a + 3);
    	if (map[pii(a[0], a[1])]) add(map[pii(a[0], a[1])], i); else map[pii(a[0], a[1])] = i;
    	if (map[pii(a[0], a[2])]) add(map[pii(a[0], a[2])], i); else map[pii(a[0], a[2])] = i;
    	if (map[pii(a[1], a[2])]) add(map[pii(a[1], a[2])], i); else map[pii(a[1], a[2])] = i;
    }
    rt = 1; dep[rt] = 1; Dfs(rt, 0);
    for (int i = 1; i <= n - 2; ++i) if (dep[i] > dep[rt]) rt = i;
    dep[rt] = 1; Dfs(rt, 0);
    for (int i = 1; i <= n - 2; ++i) ans = std::max(ans, dep[i]);
    return printf("%d\n", ans), 0;
}
