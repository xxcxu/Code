#include <bits/stdc++.h>
#define function auto
#define boolean bool
inline function freopenI(std::string name) -> void {freopen((name + ".in").c_str(), "r", stdin);}
inline function freopenO(std::string name) -> void {freopen((name + ".out").c_str(), "w", stdout);}
namespace Codespace {
    static constexpr int N = 20;
    static constexpr double eps = 1e-8;
    int n, bit[1 << N];
    double ans, a[N][N];
    double f[1 << N], g[1 << N], no[N][1 << N];
    inline function lowbit(int x) -> int {return x & -x;}
    function Solver(int test_case = 0) -> void {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                scanf("%lf", &a[i][j]), a[i][j] -= eps;
        for (int i = 1; i < 1 << n; ++i) bit[i] = i & 1 ? 1 : bit[i / 2] + 1;
        for (int i = 1; i <= n; ++i) {
            no[i][0] = 1.0;
            for (int j = 1; j < 1 << n; ++j)
                no[i][j] = no[i][j & (j - 1)] * (1.0 - a[i][bit[j]]);
        }
        for (int i = 1, t; i < 1 << n; ++i) {
            f[i] = g[i] = 1.0, t = ((1 << n) - 1) ^ i;
            double p = 1.0;            for (int j = 1; j <= n; ++j) if (i >> (j - 1) & 1) p *= no[j][t];
            for (int j = (i - 1) & i; j; j = (j - 1) & i) 
                if (j & lowbit(i)) {
                    int mask = j ^ i, low = lowbit(mask);
                    g[j] = g[j ^ low] / no[bit[low]][mask] * no[bit[low]][j];
                    f[i] -= f[j] * g[j];
                }
            ans += f[i] * p;
        }
        printf("%.7lf\n", ans);
    }
}
function main(int argv, char *argc[]) -> decltype(0) {
    freopenI("expect");
    freopenO("expect");
    Codespace::Solver();
    return 0;
}