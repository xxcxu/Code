#include <bits/stdc++.h>
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
template<const int N>
class StringHash : public HashTable {
    using ll = long long;
    #define inv(x, y) (qpow(x, y - 2, y))
    ll qpow(ll x, ll y, ll P) {
        ll ans = 1;
        for (; y; y >>= 1, x = 1ll * x * x % P)
            if (y & 1) ans = 1ll * ans * x % P;
        return ans % P;
    }
    ll m1 = 1e9 + 7, m2 = 998244353; 
    int RandInt(int l, int r) {
        static std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> random(l, r);
        return random(engine);
    }
    class FastMod {
        public: uint64_t b, m;
        public: FsatMod(uint64_t b): b(b) {
            m = (uint64_t)((__int128_t(1) << 64) / b);
        }
        public: friend uint64_t operator % (const uint64_t &a, const FastMod &P) {
            uint64_t r = (uint64_t)(a - (__int128_t(P.m) * a >> 64) * P.b);
            return r >= P.b ? r - P.b : r;
        }
    } m1(1e9 + 3), m2(1e9 + 9);
    class DoubleHash {
        public: ll v1, v2;
        public: DoubleHash() {}
        public: DoubleHash(ll a) {v1 = v2 = a;}
        public: DoubleHash(ll a, ll b) {v1 = a; v2 = b;}
        public: DoubleHash operator * (ll val) const {return {(v1 * val) % m1, (v2 * val) % m2};}
        public: DoubleHash operator + (ll val) const {return {(v1 + val) % m1, (v2 + val) % m2};}
        public: DoubleHash operator - (ll val) const {return {(v1 + m1 - val) % m1, (v2 + m2 - val) % m2};}
        public: DoubleHash operator * (const DoubleHash &a) {return {(v1 * a.v1) % m1, (v2 * a.v2) % m2};}
        public: DoubleHash operator / (const DoubleHash &a) {return (*this) * DoubleHash(inv(a.v1, m1), inv(a.v2, m2));}
        public: DoubleHash operator + (const DoubleHash &a) {return {(v1 + a.v1) % m1, (v2 + a.v2) % m2};}
        public: DoubleHash operator - (const DoubleHash &a) {return {(v1 + m1 - a.v1) % m1, (v2 + m2 - a.v2) % m2};}
        public: DoubleHash operator ^ (const DoubleHash &a) {return {(v1 ^ a.v1) % m1, (v2 ^ a.v2) % m2};}
        public: bool operator == (const DoubleHash &a) const {return v1 == a.v1 && v2 == a.v2;}
        public: bool operator < (const DoubleHash &a) const {
            if (v1 != a.v1) return v1 < a.v1;
            return v2 < a.v2;
        }
        public: friend DoubleHash qpow(DoubleHash x, ll y) {
            DoubleHash ans(1);
            for (; y > 0; y >>= 1, x = x * x)
                if (y & 1) ans = ans * x;
            return ans;
        }
    } Base(RandInt(31, 1e9), RandInt(33, 5e8));
    DoubleHash pown[N], p[N], q[N];
    DoubleHash GetPre(int l, int r) {return p[r] - p[l - 1] * pown[r - l + 1];}
    DoubleHash GetSuf(int l, int r) {return q[l] - q[r - 1] * pown[r - l + 1];}
    void Init() {
        pown[0] = DoubleHahs(1, 1);
        for (int i = 1; i < N; ++i) pown[i] = pown[i - 1] * Base;
    }
    void PreHash(int n, const char str[], DoubleHash h[]) {
        h[0] = DoubleHash(0, 0);
        for (int i = 1; i <= n; ++i) h[i] = h[i - 1] * Base + str[i];
    }
    void SufHash(int n, const char str[], DoubleHash h[]) {
        h[n + 1] = DoubleHash(0, 0);
        for (int i = n; i >= 1; --i) h[i] = h[i + 1] * Base + str[i];
    }
};