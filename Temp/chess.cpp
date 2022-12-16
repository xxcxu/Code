#include <bits/stdc++.h>
namespace Switch {
    #define function auto
    #define boolean bool
    #define FREOPEN // IO交互
    #define MULTIPLE // 多组数据
    // #define DEBUG // 调试信息
    boolean isfreopen = false;
    boolean ismultiple = false;
    boolean isdebug = false;
}
namespace IO {
    const int precision = 4;
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
    static constexpr int N = 1e3 + 5;
    int n, m, cnt, col[N], rol[N];
    ll s, c, sum;
    char map[N][N];
    function Solver(int test_case = 0) -> void {
        std::memset(col, 0, sizeof col);
        std::memset(rol, 0, sizeof rol);
        read(n, m); cnt = 0; sum = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%s", map[i] + 1);
            for (int j = 1; j <= m; ++j)
                if (map[i][j] == 'G') col[i] = j, rol[j] = i;
                else ++ cnt;
        }
        s = 0, c = 0;
        for (int i = 1; i <= n; ++i) {
            ll cur = m - (bool)col[i];
            sum += (i * c - s) * cur;
            s += i * cur; c += cur;
        }
        s = 0, c = 0;
        for (int i = 1; i <= m; ++i) {
            ll cur = n - (bool)rol[i];
            sum += (i * c - s) * cur;
            s += i * cur; c += cur;
        }
        for (int i = 1; i <= n; ++i) if (col[i]) sum += 2ll * (col[i] - 1) * (m - col[i]);
        for (int i = 1; i <= m; ++i) if (rol[i]) sum += 2ll * (rol[i] - 1) * (n - rol[i]);
        
        for (int s = 0; s < 2; ++s) {
            ll ss = 0;
            for (int i = 1; i <= n; ++i) {
                if (!col[i]) {ss = 0; continue;}
                if (col[i - 1] && (col[i] > col[i - 1]) == s)
                    sum += 1ll * ss * (s ? m - col[i] : col[i] - 1);
                else
                    ss = 0;
                ss += (s ? col[i] - 1 : m - col[i]) * 2ll;
            }
        }
        for (int s = 0; s < 2; ++s) {
            ll ss = 0;
            for (int i = 1; i <= m; ++i) {
                if (!rol[i]) {ss = 0; continue;}
                if (rol[i - 1] && (rol[i] > rol[i - 1]) == s)
                    sum += 1ll * ss * (s ? n - rol[i] : rol[i] - 1);
                else
                    ss = 0;
                ss += (s ? rol[i] - 1 : n - rol[i]) * 2ll;
            }
        }   
        sum = sum * 2;
        printf("%.4lf\n", 1.0 * sum / cnt / cnt);
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
    // if (isfreopen) freopenI("chess"), freopenO("chess");
    if (ismultiple) read(T); else T = 1;
    while (T--) Codespace::Solver(++ Case);
    return 0;
}
/*
1
4 4
G###
###G
####
#G##

(1,2) 33
(1,3) 32
(1,4) 
*/