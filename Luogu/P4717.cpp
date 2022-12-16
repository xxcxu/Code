#include <bits/stdc++.h>
const int N = 1 << 18, mod = 998244353;
template<int N, int mod>
class FastWalshHadamardTransform {
    private: int Cng(int x) {return (x % mod + mod) % mod;}
    private: int Add(int x, int y) {x = Cng(x), y = Cng(y); return (x + y) % mod;}
    private: int Mul(int x, int y) {x = Cng(x), y = Cng(y); return 1ll * x * y % mod;}
    private: void Madd(int &x, int y) {x = Add(x, y);} 
    private: void Mmul(int &x, int y) {x = Mul(x, y);}
    public: int Fpow(int x, int y) {int ans = 1; for (; y; y >>= 1, Mmul(x, x)) if (y & 1) Mmul(ans, x); return ans;}
    public: int n, A[N], B[N], a[N], b[N];
    public: void Copy() {memcpy(a, A, sizeof A); memcpy(b, B, sizeof B);}
    public: void Mul() {for (int i = 0; i < n; ++i) Mmul(a[i], b[i]);}
    public: void Print() {for (int i = 0; i < n; ++i) printf("%d ", a[i]); puts("");}
    #define for1 for (int i = 1; i < n; i <<= 1)
    #define for2 for (int p = i << 1, j = 0; j < n; j += p)
    #define for3 for (int k = 0; k < i; ++k)
    public: void Or(int *a, int op) {for1 for2 for3 Madd(a[i + j + k], Mul(a[j + k], op));}
    public: void And(int *a, int op) {for1 for2 for3 Madd(a[j + k], Mul(a[i + j + k], op));}
    public: void Xor(int *a, int op) {
        for1 for2 for3 {
            int x = a[j + k], y = a[i + j + k];
            a[j + k] = Add(x, y), a[i + j + k] = Add(x, -y);
            Mmul(a[j + k], op); Mmul(a[i + j + k], op);
        }
    }
};
FastWalshHadamardTransform<N, mod> FWT;
signed main() {
    scanf("%d", &FWT.n); FWT.n = 1 << FWT.n; // atention
    for (int i = 0; i < FWT.n; ++i) scanf("%d", &FWT.A[i]);
    for (int i = 0; i < FWT.n; ++i) scanf("%d", &FWT.B[i]);
    FWT.Copy(); FWT.Or(FWT.a, 1); FWT.Or(FWT.b, 1); FWT.Mul(); FWT.Or(FWT.a, -1); FWT.Print();
    FWT.Copy(); FWT.And(FWT.a, 1); FWT.And(FWT.b, 1); FWT.Mul(); FWT.And(FWT.a, -1); FWT.Print();
    FWT.Copy(); FWT.Xor(FWT.a, 1); FWT.Xor(FWT.b, 1); FWT.Mul(); FWT.Xor(FWT.a, FWT.Fpow(2, mod - 2)); FWT.Print();
    return 0;
}