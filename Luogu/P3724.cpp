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

#define int long long
#define x first
#define y second

using pii = std::pair<int, int>;
static constexpr int N = 1e2 + 5;

int n, m, mc, max, day, cnt;
int a[N], w[N], c[N], f[N][N];
pii atc[N * N * N];

void cmax(int &x, int y) {x = std::max(x, y);}

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
};
class PairHash : public HashTable {
    public: size_t operator() (const std::pair<int, int> &p) const {
        size_t h1 = Hash(p.first), h2 = Hash(p.second);
        return (h1 << 31) ^ (h2 >> 31);
    }
};
class RealHash {
    std::unordered_map<uint64_t, bool> s;
    PairHash t;
    public: void add(int x, int y) {s[t(pii(x, y))] = true;}
    public: void del(int x, int y) {s.erase(s.find(t(pii(x, y))));}
    public: bool query(int x, int y) {return s.count(t(pii(x, y)));}
} hash_table;

void bfs() {
    class node {
        public: int day, attack, level;
        public: node(int day, int attack, int level): 
            day(day), attack(attack), level(level) {}
    };
    std::queue<node> q;
    q.emplace(1, 1, 0);
    while (q.size()) {
        auto [d, at, l] = q.front(); q.pop();
        if (d == day) continue;
        q.emplace(d + 1, at, l + 1);
        if (l > 1 && at * l <= max && !hash_table.query(at * l, d + 1)) {
            q.emplace(d + 1, at * l, l);
            atc[++ cnt] = pii(at * l, d + 1);
            hash_table.add(at * l, d + 1);
        }
    } return void();
}

signed main() {
    read(n, m, mc);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) read(w[i]);
    for (int i = 1; i <= m; ++i) read(c[i]);
    for (int i = 1; i <= m; ++i) cmax(max, c[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = a[i]; j <= mc; ++j) {
            cmax(f[i][j - a[i]], f[i - 1][j] + 1);
            cmax(f[i][std::min(j - a[i] + w[i], mc)], f[i - 1][j]);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= mc; ++j) cmax(day, f[i][j]);
    bfs(); std::sort(atc + 1, atc + cnt + 1);
    for (int i = 1; i <= m; ++i) {
        if (day >= c[i]) {puts("1"); continue;}
        bool flag = false; int min = 1e9;
        for (int j = cnt, k = 1; j >= 1; --j) {
            while (k < cnt && atc[j].x + atc[k].x <= c[i]) 
                 min = std::min(min, atc[k].y - atc[k].x), ++k;
                      if (min + c[i] - atc[j].x <= day - atc[j].y) {flag = true; break;}
            if (atc[j].x <= c[i] && c[i] - atc[j].x <= day - atc[j].y) {flag = true; break;}
        } puts(flag ? "1" : "0");
    } 
    return 0;
}