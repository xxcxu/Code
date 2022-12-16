#include <bits/stdc++.h>
const int P = 1e9, N = 5e5 + 5, inf = P - 1;
int Rev(int x) {return (x % P + P) % P;}
int Add(int x, int y) {x = Rev(x), y = Rev(y); return (x + y) % P;}
template<typename ...Args>
int Add(int x, Args ...args) {return Add(x, Add(args...));}
void cAdd(int &x, int y) {x = Add(x, y);}
template<typename ...Args>
void cAdd(int &x, Args ...args) {x = Add(x, args...);}
int Mul(int x, int y) {x = Rev(x), y = Rev(y); return 1ll * x * y % P;}
template<typename ...Args>
int Mul(int x, Args ...args) {return Mul(x, Mul(args...));}
void cMul(int &x, int y) {x = Mul(x, y);}
template<typename ...Args>
void cMul(int &x, Args ...args) {x = Mul(x, args...);}
int n, ans, a[N];
int Calc(int l, int r) {
    int c = l + r, len = r - l + 1;
    return 1ll * c * len / 2 % P;
}
void Solve(int l, int r) {
    static std::function<int(int)> sqr = [](int x) {return 1ll * x * x % P;};
    static int min[N], max[N], sum[7][N];
    if (l == r) return void(cAdd(ans, sqr(a[l])));
	int mid = (l + r) >> 1;
    Solve(l, mid); Solve(mid + 1, r);
    min[mid] = inf, max[mid] = -inf;
    for (int i = 1; i < 7; ++i) sum[i][mid] = 0;
    for (int i = mid + 1; i <= r; ++i) {
        min[i] = std::min(min[i - 1], a[i]);
        max[i] = std::max(max[i - 1], a[i]);
        sum[1][i] = Add(sum[1][i - 1], Mul(max[i], i));
        sum[2][i] = Add(sum[2][i - 1], max[i]);
        sum[3][i] = Add(sum[3][i - 1], Mul(min[i], i));
        sum[4][i] = Add(sum[4][i - 1], min[i]);
        sum[5][i] = Add(sum[5][i - 1], Mul(min[i], max[i], i));
        sum[6][i] = Add(sum[6][i - 1], Mul(min[i], max[i]));
    }
    int mn = inf, mx = -inf, i = mid, j = mid;
    for (int x = mid; x >= l; --x) {
        mn = std::min(mn, a[x]);
        mx = std::max(mx, a[x]);
        while (min[i + 1] >= mn && i < r) ++ i;
        while (max[j + 1] <= mx && j < r) ++ j;
        int q = std::min(i, j), p = std::max(i, j);
        #ifdef DEBUG
            assert(p != q);
        #endif
        cAdd(ans, Mul(mn, mx, Calc(mid + 2 - x, q - x + 1)));
        if (q == j) cAdd(ans, Mul(mn, Add(sum[1][p], -sum[1][q], -Mul(x - 1, Add(sum[2][p], -sum[2][q])))));
        else cAdd(ans, Mul(mx, Add(sum[3][p], -sum[3][q], -Mul(x - 1, Add(sum[4][p], -sum[4][q])))));
        cAdd(ans, sum[5][r], -sum[5][p], -Mul(x - 1, Add(sum[6][r], -sum[6][p])));
    } return void();
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    Solve(1, n); return printf("%d\n", Add(ans, P)), 0;
}