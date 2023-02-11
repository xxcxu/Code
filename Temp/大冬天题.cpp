#include <bits/stdc++.h>
const int N = 1005;
class Int {
    private: int n, a[N];
    public : Int(int x = 0) {
        n = 0;
        if (x == 0) a[n = 1] = 0;
        else while (x) a[++ n] = x % 10, x /= 10;
    }
    public : int& operator [] (int b) & {return a[b];}
    public : const  int& operator [] (int b) const& {return a[b];}
    public : friend Int  operator +  (const Int &a, int  b) {
        Int c = a;
        c[1] += b;
        for (int i = 1; i <= c.n; ++i) {
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
        while (c[c.n + 1]) {
            ++ c.n;
            c[c.n + 2] += c[c.n + 1] / 10;
            c[c.n + 1] %= 10;
        }
        return c;
    }
    public : friend Int  operator +  (const Int &a, const Int &b) {
        Int c = Int();
        int n = a.n, m = b.n;
        for (int i = 1; (i <= n) || (i <= m); ++i) {
            c[i]     = a[i] + b[i];
            c[i + 1] += c[i] / 10;
            c[i]     %= 10;
        }
        int& nn = c.n;
        nn = std::max(n, m);
        while (c[nn + 1]) {
            ++ nn;
            c[nn + 2] += c[nn + 1] / 10;
            c[nn + 1] %= 10;
        }
        return c;
    }
    public : friend Int  operator -  (const Int &a, const Int &b) {
        Int c = Int();
        int n = a.n, m = b.n;
        for (int i = 1; (i <= n) || (i <= m); ++i) {
            if (a[i] + c[i] < b[i]) -- c[i + 1], c[i] += 10;
            c[i] += a[i] - b[i];
        }
        int& nn = c.n;
        nn = std::max(n, m);
        while (c[nn + 1] == 0) -- nn;
        return c;
    }
    public : friend Int  operator -  (const Int &a, int b) {return a - Int(b);}
    public : friend Int& operator += (Int &a, int  b) {return a = a + b;}
    public : friend Int& operator += (Int &a, const Int &b) {return a = a + b;} 
    public : friend bool operator <  (const Int &a, const Int &b) {
        int n = a.n, m = b.n;
        if (n > m) return false;
        if (n < m) return true;
        for (int i = n; i >= 1; --i) {
            if (a[i] < b[i]) return true;
            if (a[i] > b[i]) return false;
        } return false;
    }
    public : friend bool operator >  (const Int &a, const Int &b) {return b < a;}
    public : friend bool operator == (const Int &a, const Int &b) {return !(a < b) && !(a > b);}
    public : friend bool operator <= (const Int &a, const Int &b) {return (a < b) || (a == b);}
    public : friend bool operator >= (const Int &a, const Int &b) {return (a > b) || (a == b);}
    public : void reverse() {
        for (int i = 1; i <= n / 2; ++i) std::swap(a[i], a[n - i + 1]);
        while (!a[n]) -- n;
    }
    public : void read()  {
        char ch = getchar();
        for (; isdigit(ch); ch = getchar()) a[++ n] = ch - '0';
        (*this).reverse();
    }
    public : void print() {for (int i = n; i >= 1; --i) printf("%d", a[i]);}
};
Int n; int k;
void solve(int k) {
    Int l = n - 2 * k + 1, r = n + 2 * k + 1; 
    Int match = 0;
    for (int i = 1; i <= 25; ++i)
        if (n <= l + (1 << i) && l + (1 << i) <= r)
            {match = l + (1 << i); break;}
    if (match == 0) return void();
    int cnt = 0;
    while (l <= n && match <= r) {
        l.print(); putchar(' ');
        match.print(); puts("");
        ++ cnt, l += 2; match += 2;
    }
    solve(k - cnt);
    return void();
}
signed main() {
    n.read();
    scanf("%d", &k);
    solve(k);    
}
/*
ZJ-120
gzcSexTY
*/