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
    static constexpr int N = 2e5 + 5;
    int n, m;
    function Clear() -> void {}
    class SegmentTree2 {
        #define ls (rt << 1)
        #define rs (rt << 1 | 1)
        private: class TreeNode {
            public: int l, r, max;
            public: std::priority_queue<int> q;
        } tr[N << 2];
        private: function Pushup(int rt) -> void {
            tr[rt].max = tr[rt].q.top();
            if (tr[rt].l != tr[rt].r) 
                tr[rt].max = std::max({tr[rt].max, tr[ls].max, tr[rs].max});
        }
        private: function Pushtag(int rt, int x) -> void {
            tr[rt].q.emplace(x); Pushup(rt);
        }
        private: function Pushdown(int rt, int x) -> void {
            if (tr[rt].q.top() == x) {
                Pushtag(ls, x);
                Pushtag(rs, x);
                tr[rt].q.pop();
            }
        }
        public: function Build(int rt, int l, int r) -> void {
            tr[rt].l = l, tr[rt].r = r;
            tr[rt].max = -1, tr[rt].q.emplace(-1);
            if (l == r) return void();
            int mid = (l + r) >> 1;
            Build(ls, l, mid); Build(rs, mid + 1, r);
        }
        public: function Insert(int rt, int l, int r, int v) -> void {
            if (l <= tr[rt].l && tr[rt].r <= r) {
                tr[rt].q.emplace(v);
                return Pushup(rt);
            }
            int mid = (tr[rt].l + tr[rt].r) >> 1;
            if (l <= mid) Insert(ls, l, r, v);
            if (r > mid) Insert(rs, l, r, v);
            Pushup(rt);
        }
        public: function Update(int rt, int l, int r, int v) -> void {
            if (l <= tr[rt].l && tr[rt].r <= r) {
                if (tr[rt].max != v) return;
                if (tr[rt].q.top() == v) {
                    tr[rt].q.pop();
                    return Pushup(rt);
                }
            }
            Pushdown(rt, v);
            int mid = (tr[rt].l + tr[rt].r) >> 1;
            if (l <= mid && tr[ls].max >= v) Update(ls, l, r, v);
            if (r > mid && tr[rs].max >= v) Update(rs, l, r, v);
            Pushup(rt);
        }
        public: function Query(int rt, int l, int r) -> int {
            if (l <= tr[rt].l && tr[rt].r <= r) return tr[rt].max;
            int mid = (tr[rt].l + tr[rt].r) >> 1, ans = tr[rt].q.top();
            if (l <= mid) ans = std::max(ans, Query(ls, l, r));
            if (r > mid) ans = std::max(ans, Query(rs, l, r));
            return ans;
        }
    };
    function Solver(int test_case = 0) -> void {
        read(n, m);
        SegmentTree2* Tree = new SegmentTree2;
        Tree -> Build(1, 1, n);
        for (int i = 1, opt, l, r, v; i <= m; ++i) {
            read(opt, l, r);
            if (opt == 1) read(v), Tree -> Insert(1, l, r, v);
            if (opt == 2) {
                int k = Tree -> Query(1, l, r);
                if (k != -1) Tree -> Update(1, l, r, k);
            }
            if (opt == 3) write(Tree -> Query(1, l, r), '\n');
        }
        delete Tree;
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
    if (isfreopen) freopenI("sorrow"), freopenO("sorrow");
    if (ismultiple) read(T); else T = 1;
    while (T--) Codespace::Solver(++ Case);
    return 0;
}