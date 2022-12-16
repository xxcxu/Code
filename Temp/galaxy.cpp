#include <bits/stdc++.h>
#define eb emplace_back
using pii = std::pair<int, int>;
static constexpr int N = 5e5 + 5, M = 1e3 + 5;
int n, m, q;
size_t Hash, CHK;
size_t val[N], c[N], s[N];
class HashTable {
    public: static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    public: static size_t Hash(uint64_t x) {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
class CustomHash : public HashTable {
    public: size_t operator() (const uint64_t x) const {
        return Hash(x);
    }
} HashTable;
signed main() {
	scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) val[i] = HashTable(i) * HashTable(i);
	for (int i = 1; i <= m; ++i) {
		static int u, v;
		scanf("%d%d", &u, &v);
        s[v] += val[u], c[v] += val[u];
        Hash += val[u];
	}
    for (int i = 1; i <= n; ++i) CHK += val[i];
	scanf("%d", &q);
	while (q--) {
		static int t, u, v;
		scanf("%d%d", &t, &u);
		if (t == 1 || t == 3) scanf("%d", &v);
             if (t == 1) c[v] -= val[u], Hash -= val[u];
		else if (t == 2) Hash -= c[u], c[u] = 0;
		else if (t == 3) c[v] += val[u], Hash += val[u];
        else if (t == 4) Hash += s[u] - c[u], c[u] = s[u];
		puts(Hash == CHK ? "YES" : "NO");
	}
}