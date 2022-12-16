#include <bits/stdc++.h>

#define eb emplace_back

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
        Range(T l = 0, T r = 0): __begin(l), __end(r + 1) {}
        Iterator<T> begin() {return Iterator<T>(__begin);}
        Iterator<T> end() {return Iterator<T>(__end);}
    private:
        T __begin;
        T __end;
};

static constexpr int N = 2e6 + 5, P = 1e9 + 7;

int n, m, ans, redius = 1, scc_cnt;
int f[N], bel[N], dfn[N], pow2[N], size[N], size2[N], size3[N];
std::vector<int> e[N], graph[N];

int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}

void tarjan(int x, int fa) {
    static int time_stamp = 0, top = 0;
    static int stack[N], low[N];
    dfn[x] = low[x] = ++ time_stamp;
    stack[++ top] = x;
    for (auto y : e[x]) {
        if (y == fa) continue;
        if (!dfn[y]) tarjan(y, x), low[x] = std::min(low[x], low[y]);
        else low[x] = std::min(low[x], dfn[y]);
    }
    if (dfn[x] == low[x]) {
        int u; ++ scc_cnt;
        do {
            u = stack[top --];
            bel[u] = scc_cnt;
            ++ size[scc_cnt];
        } while (u != x);
    }
    return void();
}

void rebuild() {
    for (auto i : Range<int>(1, n))
        for (auto j : e[i])
            if (bel[i] != bel[j]) graph[bel[i]].eb(bel[j]);
            else if (i < j) redius = mul(redius, 2);
    return void();
}

void init() {
    pow2[0] = 1;
    for (auto i : Range<int>(1, n + m)) pow2[i] = mul(pow2[i - 1], 2);
    return void();
}

void DpTree(int x, int fa) {
    size3[x] = 1;
    f[x] = pow2[size[x]] - 1;
    for (auto y : graph[x]) {
        if (y == fa) continue;
        DpTree(y, x);
        f[x] = inc(inc(mul(pow2[size3[x] - 1], f[y]), mul(pow2[size3[y]], f[x])), mul(f[x], f[y]));
        size3[x] += size3[y];
    }
    if (x != 1) ans = inc(ans, mul(f[x], pow2[scc_cnt - size3[x] - 1]));
    else ans = inc(ans, f[x]);
    return void();
}

signed main() {
    read(n, m);
    for (auto i : Range<int>(1, m)) {
        static int u, v;
        read(u, v); e[u].eb(v); e[v].eb(u);
    }
    tarjan(1, 0);
    rebuild();
    init();
    DpTree(1, 0);
    printf("%d\n", mul(redius, ans));
    return 0;
}