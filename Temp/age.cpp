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
using ld = long double;
namespace Codespace {
    static constexpr ll N = 100;
    static constexpr ld eps = 1e-9;
    ll y, d, b, limit, tot, cnt, t[N], tl[N];
    function Big() -> bool {
        if (cnt != tot) return cnt > tot;
        for (ll i = cnt; i >= 1; --i)
            if (t[i] != tl[i]) return t[i] > tl[i];
        return true;
    }
    function Init() -> ll {
        ll tmp = d; tot = 0;
        while (tmp) tl[++ tot] = tmp % 10, tmp /= 10;
        ll l = 10, r = y, ans;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            tmp = y, cnt = 0;
            while (tmp) t[++ cnt] = tmp % mid, tmp /= mid;
            if (Big()) l = mid + 1, ans = mid;
            else r = mid - 1;
        }
        return ans;
    }
    function Find(ll i) -> ll {
        if (i >= 100) {
            ll a = i / 100, b = (i / 10) % 10, c = i % 10;
            c -= y;
            ld delta = (ld)b * b - (ld)4.0 * a * c;
            if (delta - eps >= 0) {
                delta = std::max(delta, (ld)0);
                delta = std::sqrt(delta);
                ld a0 = ((ld)-b + delta) / ((ld)2.0 * a);
                ld a1 = ((ld)-b - delta) / ((ld)2.0 * a);
                ll x0 = std::round(a0), x1 = std::round(a1);
                if (x0 < 10 || x0 > limit || a * x0 * x0 + b * x0 + c != 0) x0 = -1;
                if (x1 < 10 || x1 > limit || a * x1 * x1 + b * x1 + c != 0) x1 = -1;
                return std::max(x0, x1);
            } else return -1;
        }
        else {
            ll a = i / 10, b = i % 10;
            b = y - b;
            if (b % a) return -1;
            if (b / a > limit) return -1;
            return b / a;
        }
    }
    function Solver(int test_case = 0) -> void {
        read(y, d); limit = Init(); b = 10;
        for (ll i = 10; i < 1000; ++i) b = std::max(b, Find(i));
        for (ll i = 10; i <= limit && i <= 1000000; ++i) {
            bool ok = true;
            for (ll p = 1; ok && p < y && p > 0; p *= i) {
                if ((y / p) % i > 9) ok = false;
                if ((y / p) % i < 0) ok = false;
                ld np = (ld)p * i;
                if (np > (ld)y - eps) break; 
            }
            if (ok) b = std::max(b, (ll)i);
        }
        write(b, '\n');
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
    if (isfreopen) freopenI("age"), freopenO("age");
    if (ismultiple) read(T); else T = 1;
    while (T--) Codespace::Solver(++ Case);
    return 0;
}