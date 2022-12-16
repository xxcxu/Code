#include <bits/stdc++.h>
namespace Switch {
    #define function auto
    #define boolean bool
    // #define FREOPEN // IO交互
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
            T x = 0; boolean f = false; char ch = getchar();
            for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
            for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
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
    static constexpr int N = 5e3 + 5, P = 1e9 + 7; 
    int n, g[N], h[N], size[N], f[N][N << 1];
    std::vector<int> e[N];
    namespace modint {
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
    };
    using namespace modint;
    function Dfs(int x, int pre) -> void {
        size[x] = f[x][1] = 1;
        for (int y : e[x]) if (y != pre) {
            Dfs(y, x);
            for (int i = 0; i <= size[x]; ++i) 
                g[i] = f[x][i], f[x][i] = 0;
            for (int i = 0; i <= size[x]; ++i)
                for (int j = 0; j <= size[y]; ++j)
                    cAdd(f[x][i + j], Mul(g[i], f[y][j]));
            size[x] += size[y];
        }
        for (int i = 2; i <= size[x]; i += 2)
            cAdd(f[x][0], Mul(P - h[i], f[x][i]));
        return void();
    }
    function Solver(int test_case = 0) -> void {
        read(n);
        for (int i = 1, u, v; i < n; ++i) {
            read(u, v);
            e[u].emplace_back(v);
            e[v].emplace_back(u);
        } h[0] = 1;
        for (int i = 2; i <= n; ++i) h[i] = Mul(h[i - 2], i - 1);
        Dfs(1, 0);
        return write(P - f[1][0], '\n');
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
    if (isfreopen) freopenI(realname), freopenO(realname);
    if (ismultiple) read(T); else T = 1;
    while (T--) Codespace::Solver(++ Case);
    return 0;
}