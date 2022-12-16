#include <bits/stdc++.h>
#define int long long
using db = double;
static constexpr int N = 3e2 + 5, inf = 1e9 + 7;
void cmin(int &x, int y) {if (y < x) x = y;}
void cmax(int &x, int y) {if (y > x) x = y;}
template<const int LEN>
class Interger {
    private: int n, a[LEN];
    public: Interger(): n(1) {a[1] = 0;}
    public: Interger(int x) {
        if (x == 0) a[n = 1] = 0;
        else while (x) a[++ n] = x % 10, x /= 10;
    }
    public: Interger operator * (const int b) {
        Interger c; c.n = n;
        for (int i = 1; i <= n; ++i) c.a[i] = a[i] * b;
        for (int i = 1; i <= n; ++i) c.a[i + 1] += c.a[i] / 10, c.a[i] %= 10;
        while (c.a[c.n + 1]) {
            ++ c.n;
            c.a[c.n + 1] += c.a[c.n] / 10;
            c.a[c.n] %= 10;
        }
        return c;
    }
    public: void write() {for (int i = n; i >= 1; --i) putchar(char(a[i] + '0'));}
};
Interger<114514> answer(1);
int n, m, a, b, c, d, pos; db ans;
int mat[N][N]; db mat2[N][N], mul1[N][N], mul2[N][N];
signed main() {
    freopen("frame.in", "r", stdin);
    freopen("frame.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) 
            scanf("%lld", mat[i] + j);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) 
            mat2[i][j] = std::log(mat[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) 
            mul1[i][j] = mul1[i][j - 1] + mat2[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) 
            mul2[i][j] = mul2[i - 1][j] + mat2[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            db min = inf;
            for (int k = 1; k <= m; ++k) {
                db res1 = mul1[i][k] + mul1[j][k] + mul2[j - 1][k] - mul2[i][k] - min;
                db res2 = mul1[i][k - 1] + mul1[j][k - 1] - mul2[j - 1][k] + mul2[i][k];
                if (ans < res1) ans = res1, a = i, b = j, c = pos, d = k;
                if (min > res2) min = res2, pos = k;
            }
        }
    for (int i = a + 1; i < b; ++i) answer = answer * mat[i][c];
    for (int i = a + 1; i < b; ++i) answer = answer * mat[i][d];
    for (int i = c; i <= d; ++i) answer = answer * mat[a][i]; 
    for (int i = c; i <= d; ++i) answer = answer * mat[b][i];
    answer.write(); puts("");
    return 0;
}