/*
 * @Author: Maraschino 
 * @Date: 2022-09-22 20:30:58 
 * @Last Modified by: Maraschino
 * @Last Modified time: 2022-09-22 20:36:02
 */
#include <bits/stdc++.h>
namespace Switch {
    #define function auto
    #define boolean bool
    // #define FREOPEN // IO交互
    // #define MULTIPLE // 多组数据
    // #define DEBUG // 调试信息
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
    static constexpr int N = 2e2 + 5;
    static constexpr ll inf = 0x3f3f3f3f3f3f3f;
    int n, a[N]; ll l;
    char s[N][N];
    class Matrix {
        private: int n, m;
        public: std::vector<std::vector<ll>> a;
        public: Matrix(int n = 0, int m = 0, int p = 0): n(n), m(m) {
            a.resize(n, std::vector<ll>(m, -inf));
            if (p) for (int i = 0; i < n; ++i) a[i][i] = 0;
        }
        public: std::vector<ll>& operator [] (int x) & {return a[x];}
        public: const std::vector<ll>& operator[](int x) const& {return a[x];}
        public: friend Matrix operator * (const Matrix &a, const Matrix &b) {
            Matrix ans = Matrix(a.n, b.m);
            for (int i = 0; i < a.n; ++i)
                for (int j = 0; j < b.m; ++j)
                    for (int k = 0; k < a.m; ++k)
                        ans.a[i][j] = std::max(ans.a[i][j], a.a[i][k] + b.a[k][j]);
            return ans;
        }
        public: function Unit() -> void {
            assert(n == m);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j) 
                    a[i][j] = (i == j ? 0ll : -inf);
            return void();
        }
        public: friend Matrix operator ^ (Matrix a, ll k) {
            Matrix ans = Matrix(a.n, a.m, 1ll);
            for (; k; k >>= 1, a = a * a) if (k & 1) ans = ans * a;
            return ans;
        }
    };
    class Acbot {
        public: int cnt, ch[N][26], fail[N * 26];
        public: ll con[N * 26];
        public: function Insert(int o, int x) -> void {
            int p = 0;
            for (int i = 1; s[o][i]; ++i) {
                int c = s[o][i] - 'a';
                if (!ch[p][c]) ch[p][c] = ++ cnt;
                p = ch[p][c];
            }
            con[p] += x;
        }
        public: function SpawnFail() -> void {
            std::queue<int> q;
            for (int i = 0; i < 26; ++i) if (ch[0][i]) q.emplace(ch[0][i]);
            while (q.size()) {
                int x = q.front(), y; q.pop();
                for (int i = 0; i < 26; ++i)
                    if (y = ch[x][i]; y) fail[y] = ch[fail[x]][i], q.push(y);
                    else ch[x][i] = ch[fail[x]][i];
                con[x] += con[fail[x]];
            } return void();
        }    
    } Acr;
    function Clear() -> void {}
    function Solver(int test_case = 0) -> void {
        read(n, l);
        for (int i = 1; i <= n; ++i) read(a[i]);
        for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1), Acr.Insert(i, a[i]);
        Acr.SpawnFail();
        Matrix A = Matrix(1, Acr.cnt + 1), Base = Matrix(Acr.cnt + 1, Acr.cnt + 1);
        A[0][0] = 0;
        for (int i = 0; i <= Acr.cnt; ++i)
            for (int j = 0; j < 26; ++j)
                Base[i][Acr.ch[i][j]] = std::max(Base[i][Acr.ch[i][j]], Acr.con[Acr.ch[i][j]]);
        A = A * (Base ^ l);
        ll ans = 0;
        for (int i = 0; i <= Acr.cnt; ++i) ans = std::max(ans, A[0][i]);
        write(ans, '\n');
    }
}
function main(int argv, char *argv[]) -> decltype(0) {
    std::string path = __FILE__;
    std::string::size_type iPos = path.find_last_of('/') + 1;
    std::string filename = path.substr(iPos, path.length() - iPos);
    std::string realname = filename.substr(0, filename.rfind("."));
    boolean isfreopen = false;
    #ifdef FREOPEN
        isfreopen = true;
    #endif
    boolean ismultiple = false;
    #ifdef MULTIPLE
        ismultiple = true;
    #endif
    boolean isdebug = false;
    #ifdef DEBUG
        isdebug = true;
    #endif
    int T, Case = 0;
    if (isfreopen) freopenI(realname), freopenO(realname);
    if (ismultiple) read(T); else T = 1;
    while (T--) Codespace::Solver(++ Case);
    return 0;
}