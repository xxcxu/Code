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

#define range Range<int>
template<typename T>
class Iterator {
    public:
        Iterator(T _val = 0): _value(_val) {}
        bool operator != (const Iterator &other) const {
            return this -> _value != other._value;
        }
        const T & operator *() {return _value;}
        T operator ++() {return ++ _value;}
    private:
        T _value;
};
template<typename T>
class Range {
    public:
        Range(T l = 0, T r = 0): __begin(l), __end(r + 1) {}
        Iterator<T> begin() {return Iterator<T>(__begin);}
        Iterator<T> end() {return Iterator<T>(__end);}
    private:
        T __begin;
        T __end;
};


static constexpr int N = 5e3 + 5;

int n;
std::pair<uint, uint> a[N];

uint rev(uint x) {
    uint ans = 0;
    for (int i = 31; i >= 0; --i, x >>= 1)
        ans |= (x & 1) << i;
    return ans;
}

void solve() {
    std::map<int, int> map;
    read(n);
    for (auto i : range(1, n)) {
        read(a[i].second);
        a[i].first = rev(a[i].second);
        ++ map[a[i].second];
    }
    bool flag = false;
    for (auto i : map) if (i.second >= 3) flag = true;
    if (flag) return puts("NO"), void();
    puts("YES");
    std::sort(a + 1, a + n + 1);
    for (auto i : range(1, n)) printf("%u%c", a[i].second, " \n"[i == n]);
    return void();
}

signed main() {
    int t; read(t);
    while (t--) solve();
    return 0;
}