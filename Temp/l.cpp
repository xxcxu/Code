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
int n, m, k;
bool isswap, haveans;
std::vector<std::vector<int>> matrix;

void update(int i, int j, int &res, int d) {
    if (j == 1) res += d;
    if (j > 1 && j < m) res += d * 4;
    if (j == m) res += d * 3;
}
int adjust(int i, int j, int &res) {
    if (res == k) return true;
    update(i, j, res, -1);
    matrix[i][j] = 0;
    if (res == k - 1) {
        if (j < m) return matrix[i][m] = 1, true;
        if (i < n) return matrix[i + 1][1] = 1, true;
        return false;
    }
    if (res == k - 2) {
        if (j < m - 1) return matrix[i][m - 1] = 1, true;
        if (i < n && j >= 4) return matrix[i + 1][2] = 1, true;
        return false;
    }
    if (res == k - 3) {
        if (j < m - 2) return matrix[i][m - 2] = 1, matrix[i][m] = 1, true;
        if (i < n) {
            if (j > 4) return matrix[i + 1][1] = 1, matrix[i + 1][3] = 1, true;
            if (j == 4) return matrix[i + 1][2] = 1, matrix[i][m] = 1, true;
            if (j == 3) return matrix[i + 1][1] = 1, matrix[i][m - 1] = 1, true;
            return false;
        }

        if (j != m - 2) return false;
        if (n >= 4) return false;

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j < m; ++j)
                matrix[i][j] = 1;
        for (int i = 1; i <= n; ++i) 
            matrix[i][m] = 0;
        return true;    
    }
    return false;
}
void logout(bool flag) {
    if (!flag) return puts("-1"), void();
    if (isswap) {
        for (int i = 1; i <= m; ++i, puts(""))
            for (int j = 1; j <= n; ++j)
                putchar(matrix[j][i] ? '*' : '.');
    } else {
        for (int i = 1; i <= n; ++i, puts(""))
            for (int j = 1; j <= m; ++j) 
                putchar(matrix[i][j] ? '*' : '.');
    }
}
namespace brute {
    int fi(int x) {return (x - 1) / m + 1;}
    int se(int x) {return x - (fi(x) - 1) * m;}
    bool check() {
        int res = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                res += (matrix[i][j] and matrix[i + 1][j] and matrix[i][j + 1]);
                res += (matrix[i][j] and matrix[i + 1][j] and matrix[i + 1][j + 1]);
                res += (matrix[i][j] and matrix[i][j + 1] and matrix[i + 1][j + 1]);
                res += (matrix[i + 1][j + 1] and matrix[i][j + 1] and matrix[i + 1][j]);
            }
        return res == k;
    }
    void dfs(int x) {
        if (haveans) return void();
        if (x == n * m + 1) {
            if (check())
                logout(true), haveans = true;
            return void();
        }
        matrix[fi(x)][se(x)] = 0;
        dfs(x + 1);
        matrix[fi(x)][se(x)] = 1;
        dfs(x + 1);
    }
}
void bruteforce() {
    haveans = false;
    matrix = std::vector<std::vector<int>>(n + 2, std::vector<int>(m + 2, 0));
    brute::dfs(1);
    if (!haveans) logout(false);
    return void();
}
void solve() {
 
    read(n, m, k); isswap = false; 
    if (n * m <= 16) return bruteforce();
    if (!k) {
        matrix = std::vector<std::vector<int>>(n + 2, std::vector<int>(m + 2, 0));
        logout(true);
        return void();
    }
    if (n > m) std::swap(n, m), isswap = true;
    matrix = std::vector<std::vector<int>>(n + 2, std::vector<int>(m + 2, 0));
    int res = 0;
    for (int i = 1; i <= m; ++i) matrix[1][i] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            matrix[i][j] = 1;
            update(i, j, res, 1);
            if (res >= k) return logout(adjust(i, j, res));
        }
    return logout(false);
}
signed main() {
    freopen("l.in", "r", stdin); 
    freopen("l.out", "w", stdout);
    int t; read(t);
    while (t--) solve();
    return 0;
}