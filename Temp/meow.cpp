#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define range(l, r) Range<int>(l, r + 1)

template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}

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
        Range(T l = 0, T r = 0): __begin(l), __end(r) {}
        Iterator<T> begin() {return Iterator<T>(__begin);}
        Iterator<T> end() {return Iterator<T>(__end);}
    private:
        T __begin;
        T __end;
};

using pii = std::pair<int, int>;

static constexpr int N = 2e6 + 5;

int n, m, k;
int Time[N], last[N], a[N], pos[N];
int len[N], out[N][4];
std::set<pii, std::greater<pii>> q[3];

struct triple {
    int x, y, z;
    triple(int _x = 0, int _y = 0, int _z = 0): x(_x), y(_y), z(_z) {}
};
std::vector<triple> ans;
void put(int x, int s) {pos[x] = s; ans.eb(1, s, 0);}

void clear() {
    for (auto i : range(1, std::max({n, m, k})))
        Time[i] = last[i] = a[i] = pos[i] = len[i] = 0;
    for (auto i : range(0, 2)) q[i].clear();
    ans.clear();
}

void insert(int x) {
    last[a[x]] = x;
    if ((int)q[0].size() >= 2) {
        auto it = q[0].begin();
        int id = it -> second;
        q[0].erase(it); q[1].ep(Time[x], id);

        out[id][++ len[id]] = x;
        put(x, id);

        return void();
    }
    if ((int)q[1].size()) {
        auto it = q[1].begin();
        int t = it -> first, id = it -> second;
        q[1].erase(it); q[2].ep(Time[x] > t, id);

        out[id][++ len[id]] = x;
        put(x, id);

        return void();
    }
    if ((int)q[2].size() && q[2].begin() -> first) {
        auto it = q[2].begin();
        int id = it -> second;
        q[2].erase(it);

        out[id][++ len[id]] = x;
        put(x, id);

        return void();
    }
    auto it = q[0].begin();
    int id = it -> second;
    q[0].erase(it); q[1].ep(Time[x], id);
    out[id][++ len[id]] = x;
    put(x, id);
    
    return void();

}

void erase(int x) {
    int y = last[a[x]], id = pos[y];
    if (out[id][len[id]] == y) {
        ans.eb(1, id, 0);
        if (len[id] == 1) q[1].erase(pii(Time[out[id][1]], id));
        if (len[id] == 2) q[2].erase(pii(Time[out[id][2]] > Time[out[id][1]], id));
        -- len[id];
        if (len[id] == 0) q[0].ep(0, id);
        if (len[id] == 1) q[1].ep(Time[out[id][1]], id);
        if (len[id] == 2) q[2].ep(Time[out[id][2]] > Time[out[id][1]], id);
    }
    else {
        int tmp = q[0].begin() -> second;
        ans.eb(1, tmp, 0);
        ans.eb(2, id, tmp);
        if (len[id] == 1) q[1].erase(pii(Time[out[id][1]], id));
        if (len[id] == 2) q[2].erase(pii(Time[out[id][2]] > Time[out[id][1]], id));
        -- len[id];
        for (int l = 1; l <= len[id]; ++l) out[id][l] = out[id][l + 1];    
        if (len[id] == 0) q[0].ep(0, id);
        if (len[id] == 1) q[1].ep(Time[out[id][1]], id);
        if (len[id] == 2) q[2].ep(Time[out[id][2]] > Time[out[id][1]], id);
	} return void();
}

void solve() {
    scanf("%d%d%d", &n, &m, &k);
    clear();
    for (auto i : range(1, m)) read(a[i]);
    for (auto i : range(1, m))
        if (last[a[i]]) Time[last[a[i]]] = i, last[a[i]] = 0;
        else last[a[i]] = i;
	for (auto i : range(1, n)) q[0].ep(0, i), len[i] = 0;
    for (auto i : range(1, m)) if (Time[i]) insert(i); else erase(i);
    printf("%d\n", (int)ans.size());
    for (auto [x, y, z] : ans)
        if (x == 1) printf("%d %d\n", x, y);
        else printf("%d %d %d\n", x, y, z);
    return void();
}

signed main() {
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}