#include <bits/stdc++.h>
static constexpr int N = 1e6 + 5;
class INT {
    public: int n; int a[N];
    public: int& operator [] (int x) & {return a[x];}
    public: const int& operator[](int x) const& {return a[x];}
    public: INT(int x = 0) {
        if (x == 0) a[n = 1] = 0;
        else while (x) a[++ n] = x % 10, x /= 10;
    }
    public: void set(int m, int x) {
        n = m; a[m] = 1;
        for (int i = 1; i <= x; ++i) a[m - i] = 0;
        for (int i = 1; i <= m - x - 1; ++i) a[i] = 9;
        return void();
    }
    public: int countains() {
        int ret = 0;
        for (int i = 1; i <= n; ++i) ret += a[i];
        return ret;
    }
    public: friend bool operator > (const INT &a, const INT &b) {
        if (a.n > b.n) return true;
        if (a.n < b.n) return false;
        for (int i = a.n; i >= 1; --i) 
            if (a.a[i] > b[i]) return true;
            else if (a.a[i] < b[i]) return false;
        return false;
    }
    public: friend bool operator < (const INT &a, const INT &b) {
        if (a.n > b.n) return false;
        if (a.n < b.n) return true;
        for (int i = a.n; i >= 1; --i) 
            if (a.a[i] > b[i]) return false;
            else if (a.a[i] < b[i]) return true;
        return false;
    }
    public: friend bool operator == (const INT &a, const INT &b) {
        if (a.n != b.n) return false;
        for (int i = a.n; i >= 1; --i)
            if (a.a[i] != b[i]) return false;
        return true;
    }
    public: friend bool operator >= (const INT &a, const INT &b) {return (a > b) || (a == b);}
    public: friend bool operator <= (const INT &a, const INT &b) {return (a < b) || (a == b);}
    public: INT operator / (int b) {
        INT c = INT(0); c.n = n;
        for (int i = n; i >= 1; --i) {
            c[i] = a[i] / b;
            a[i - 1] += a[i] % b * 10;
        }
        while (c.n > 1 && !c[c.n]) -- c.n;
        return c;
    }
    public: INT operator /= (int b) {return *this = *this / b;}
    public: void write() {for (int i = n; i >= 1; --i) putchar(char(a[i] + '0')); puts("");}
} A, B;
const INT& max(const INT &a, const INT &b) {if (a > b) return a; else return b;}
const INT& min(const INT &a, const INT &b) {if (a > b) return b; else return a;}
int n;
signed main() {
    freopen("calc.in", "r", stdin);
    freopen("calc.out", "w", stdout);
    scanf("%d", &n);
    A.set(n, 0);
    A /= A.countains();
    B = A;
    for (int i = 1; i <= std::min(n - 1, 7); ++i) {
        A.set(n, i);
        A /= A.countains();
        B = min(B, A);
    }
    B.write();
    return 0;
}