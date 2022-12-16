#include <bits/stdc++.h>
namespace Switch {
    #define function auto
    #define boolean bool
    #define FREOPEN // IO交互
    // #define MULTIPLE // 多组数据
    // #define DEBUG // 调试信息
    boolean isfreopen = false;
    boolean ismultiple = false;
    boolean isdebug = false;
}
namespace IO {
    const int precision = 5;
    namespace InputStream {
        template<typename T>
        inline function read() -> T {
            T x = 0; boolean f = true; char ch = getchar();
            for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
            for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) - (ch ^ 48);
            return f ? ~x + 1 : x;
        }
        template<>
        inline function read() -> char {char ch = getchar(); for (; !isgraph(ch); ch = getchar()); return ch;}
        template<>
        inline function read() -> std::string {
            std::string str = " "; char ch = getchar();
            for (; !isgraph(ch); ch = getchar());
            for (; isgraph(ch); ch = getchar()) str += ch;
            return str;
        }
        template<>
        inline function read() -> double {
            double x = 0.0; boolean f = false; char ch = getchar();
            for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
            for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
            if (ch == '.') {double e = 1; for (; isdigit(ch); ch = getchar()) x = x + e * 0.1;}
            return f ? -x : x;
        }
        template<typename T>
        inline function read(T &x) -> void {x = read<T>();}
        template<typename T, typename ...Args>
        inline function read(T &x, Args &...args) -> void {read(x); read(args...);}
    }
    namespace OutputStream {
        function write(int x) -> void {if (x < 0) {x = ~x + 1; putchar('-');} if (x > 9) write(x / 10); putchar(x % 10 + '0');}
        function write(long long x) -> void {if (x < 0) {x = ~x + 1; putchar('-');} if (x > 9) write(x / 10); putchar(x % 10 + '0');}
        function write(double x) -> void {
            if (x == 0) {putchar('0'); putchar('.'); for (int i = 0; i < precision; ++i) putchar('0');}
            if (x < 0) {putchar('-'); write(-x);}
            else {
                double r = x - floor(x), l = floor(x);
                if (l == 0) putchar('0'); char buf[310]; int i = 0;
                while (floor(l) != 0) {buf[i ++] = floor(l - floor(l / 10) * 10); l /= 10;}
                for (int j = i - 1; j >= 0; --j) putchar(buf[j] ^ 48); putchar('.');
                for (int i = 0; i < precision - 1; ++i) putchar(int(floor(r *= 10)) ^ 48), r -= floor(r); double tmp = r * 10;
                if (int(floor(tmp * 10 - floor(tmp) * 10)) >= 5) putchar((int(floor(tmp)) + 1) ^ 48);
                else putchar(int(floor(tmp)) ^ 48);
            }
        }
        function write(char x) -> void {putchar(x);}
        function write(std::string x) -> void {for (auto ch : x) putchar(ch);}
        function write(char *x) -> void {puts(x);}
        function write(const char *x) -> void {puts(x);}
        template<typename T>
        function write(T x) -> void {write(x);}
        template<typename T, typename ...Args>
        function write(T x, Args ...args) -> void {write(x); write(args...);}
    }
}
function freopenI(std::string name) -> void {freopen((name + ".in").c_str(), "r", stdin);}
function freopenO(std::string name) -> void {freopen((name + ".out").c_str(), "w", stdout);}
using namespace Switch;
using namespace IO::InputStream;
using namespace IO::OutputStream;
using ll = long long;
namespace Codespace {
    static constexpr int N = 1e5 + 5, P = 998244353;
    int n, m, ans, dp[N], cnt[5];
    std::vector<int> e[N]; 
    function leaf(int x) -> bool {
        int son = (int)e[x].size();
        return !son;
    }
    function Dfs(int x) -> void {
        if (leaf(x)) return void(dp[x] = 2);// 1->2
        int cnt[5] = {0};
        for (int y : e[x]) {
            Dfs(y);
            ++ cnt[dp[y]];
        }
        if ((cnt[1] && cnt[2]) || cnt[3]) dp[x] = 4; // 在
        else if (cnt[1]) dp[x] = 2; // 先->先
        else if (cnt[2]) dp[x] = 1; // 先->后
        else dp[x] = 3; // 后手任意选
    }
    namespace modint {
        int fac[N], inv[N], finv[N];
        int Rev(int x) {return (x % P + P) % P;}
        int Inc(int x, int y) {x = Rev(x), y = Rev(y); return (x + y) % P;}
        template<typename ...Args>
        int Inc(int x, Args ...args) {return Inc(x, Inc(args...));}
        void cAdd(int &x, int y) {x = Inc(x, y);}
        template<typename ...Args>
        void cAdd(int &x, Args ...args) {x = Inc(x, args...);}
        int Mul(int x, int y) {x = Rev(x), y = Rev(y); return 1ll * x * y % P;}
        template<typename ...Args>
        int Mul(int x, Args ...args) {return Mul(x, Mul(args...));}
        void cMul(int &x, int y) {x = Mul(x, y);}
        template<typename ...Args>
        void cMul(int &x, Args ...args) {x = Mul(x, args...);}
        int C(int n, int m) {return Mul(fac[n], finv[m], finv[n - m]);}
        int qpow(int x, int y) {
            int ans = 1;
            for (; y; y >>= 1, cMul(x, x))
                if (y & 1) cMul(ans, x);
            return ans % P;
        }
        void Init() {
            fac[0] = fac[1] = inv[1] = finv[0] = finv[1] = 1;
            for (int i = 2; i < N; ++i) {
                fac[i] = Mul(fac[i - 1], i);
                inv[i] = Mul((P - P / i), inv[P % i]);
                finv[i] = Mul(finv[i - 1], inv[i]);
            } return void();
        }
    }
    using namespace modint;
    function Solver(int test_case = 0) -> void {
        read(m); Init();
        while (m --) {
            read(n);
            for (int i = 1; i <= n; ++i) e[i].clear();
            for (int i = 2, x; i <= n; ++i) {
                read(x);
                e[x].emplace_back(i);
            }
            Dfs(1);
            ++ cnt[dp[1]];
        }
        int res = Inc(qpow(2, cnt[3]), P - 1);
        if (cnt[3]) ans = Inc(ans, Mul(res, qpow(2, cnt[1] + cnt[2] + cnt[4])));
        for (int i = 1; i <= cnt[1]; i += 2)
            ans = Inc(ans, Mul(C(cnt[1], i), qpow(2, cnt[2] + cnt[4])));
        printf("%d\n", ans);
    }
}
function main(int argv, char *argc[]) -> decltype(0) {
    std::string path = __FILE__;
    std::string::size_type iPos = path.find_last_of('/') + 1;
    std::string filename = path.substr(iPos, path.length() - iPos);
    std::string realname = filename.substr(0, filename.rfind("."));
    #ifdef FREOPEN
        isfreopen = true;
    #endif
    #ifdef MULTIPLE
        ismultiple = true;
    #endif
    #ifdef DEBUG
        isdebug = true;
    #endif
    int T, Case = 0;
    if (isfreopen) freopenI("game"), freopenO("game");
    if (ismultiple) read(T); else T = 1;
    while (T--) Codespace::Solver(++ Case);
    return 0;
}