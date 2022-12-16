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
static constexpr int N = 2e5 + 5;
using ll = long long;
int n, a[N]; ll ans;
bool flag1, flag2;
void solve1() {
    printf("%lld\n", 1ll * n * (n - 1) / 2);
    for (int i = 1; i <= n; ++i) printf("%d ", n - i + 1);
}
void solve2() {
    printf("%lld\n", 1ll * n * (n - 1));
    for (int i = 2; i <= n; ++i) printf("%d ", i);
    printf("1");
}
namespace DataStructure {
    template<int N, int size>
    class St_Table {
        private: int f[N][size], g[N][size];
        public: void Init(int n, int *a) {
            for (int i = 1; i <= n; ++i) f[i][0] = a[i], g[i][0] = i;
            for (int j = 1; j <= size; ++j)
                for (int i = 1, fa, fb, ga, gb; i <= n - (1ll << j) + 1; ++i) {
                    fa = f[i][j - 1], fb = f[i + (1 << j - 1)][j - 1];
                    ga = g[i][j - 1], gb = g[i + (1 << j - 1)][j - 1];
                    if (fa > fb) f[i][j] = fa, g[i][j] = ga;
                    else if (fa == fb) f[i][j] = fa, g[i][j] = std::min(ga, gb);
                    else f[i][j] = fb, g[i][j] = gb;
                }
            return void();
        }
        public: int Query(int l, int r) {
            int k = std::log2(r - l + 1);
            int fl = f[l][k], fr = f[r - (1 << k) + 1][k];
            int gl = g[l][k], gr = g[r - (1 << k) + 1][k];
            if (fl > fr) return gl;
            else if (fl == fr) return std::min(gl, gr);
            else return gr;
        }
    };
    St_Table<N, 31> table;
};
using namespace DataStructure;
void solve3() {
    static int r = n;
    bool isfirst = false;
    table.Init(n, a);

    while (r) {
        int l = table.Query(1, r);
        ans += 1ll * a[l] * (r - l + isfirst);
        r = l - 1;
        isfirst = true;
    }
    printf("%lld\n", ans);
    
    r = n;
    while (r) {
        int l = table.Query(1, r);
        for (int i = l + 1; i <= r; ++i) printf("%d ", i);
        printf("%d ", l);
        r = l - 1;
    }
}
signed main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    read(n);
    flag1 = flag2 = true;
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) flag1 &= a[i] == i;
    for (int i = 1; i <= n; ++i) flag2 &= a[i] == n - i + 1;
    if (flag1) solve1();
    else if (flag2) solve2();
    else solve3();
    return 0;
}