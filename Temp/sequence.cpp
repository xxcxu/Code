#include <bits/stdc++.h>
namespace Switch {
    #define function auto
    #define boolean bool
    #define all(a) a.begin(), a.end()
    #define pb push_back
    #define eb emplace_back
    #define pu push
    #define ep emplace
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
using pii = std::pair<int, int>;
using vic = std::vector<int>;
namespace Codespace {
    static constexpr int N = 1e5 + 5, inf = 1e9 + 9;
	int n, oc, ec, last, cost0, cost1;
	int a[N], b[N], c[N], d[N];
	int ans0[N], ans1[N];
	vic pos;
    function Solve(int l, int r, int *b, int *ans, int t) -> void {
		pos.clear(); int dir = d[b[l]];
		int begin = last + 1, end = last + r - l + 1;
		for (int i = begin; i <= end; ++i) pos.eb(i * 2 - t);
		last += r - l + 1;
		if (~dir) {
			std::priority_queue<int> q;
			std::reverse(all(pos));
			int j = r;
			for (int i : pos) {
				while (j >= l && b[j] >= i) q.ep(a[b[j --]]);
				int x = q.top(); q.pop();
				ans[i] = x;
			}
		} else {
			std::priority_queue<int, vic, std::greater<int>> q;
			int j = l;
			for (int i : pos) {
				while (j <= r && b[j] <= i) q.ep(a[b[j ++]]);
				int x = q.top(); q.pop();
				ans[i] = x;
			}
		}
	}
    function StartWith(int op) -> int {
        int cst = oc = ec = 0;
		std::vector<pii> p, q;
        int type = op;
        for (int i = 1; i <= n; ++i) a[i] & 1 ? (b[++ oc] = i): (c[++ ec] = i);
		b[oc + 1] = c[ec + 1] = 0;
        for (int i = 1, j = 0, k = 0; i <= n; ++i) {
            int id = op ? b[++ j] : c[++ k];
            d[id] = id > i ? 1 : -1;
            cst += std::abs(id - i); 
            op ^= 1;
        }
       	for (int i = 2, last = 1; i <= oc + 1; ++i)
            if (d[b[i]] != d[b[i - 1]]) p.eb(last, i - 1), last = i;
    	for (int i = 2, last = 1; i <= ec + 1; ++i)
    		if (d[c[i]] != d[c[i - 1]]) q.eb(last, i - 1), last = i;
		last = 0;
		for (auto it : p) Solve(it.first, it.second, b, type ? ans1 : ans0, type ? 1 : 0);
    	last = 0;
		for (auto it : q) Solve(it.first, it.second, c, type ? ans1 : ans0, type ? 0 : 1);
		return cst;
	}
	function Check(int *a, int *b, int n) -> bool {
		for (int i = 1; i <= n; ++i)
			if (a[i] != b[i]) return a[i] < b[i];
		return true;
	}
    function Solver(int test_case = 0) -> void {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        for (int i = 1; i <= n; ++i) ans0[i] = inf;
        for (int i = 1; i <= n; ++i) ans1[i] = inf;
		if (n + 1 & 1) {
			cost1 = StartWith(1); 
			cost0 = StartWith(0); 
		} else {
			int od = 0;
			for (int i = 1; i <= n; ++i) od += (a[i] & 1);
			StartWith(od == (n + 1) / 2);
			if (od == (n + 1) / 2) cost0 = inf;
			else cost1 = inf;
		}
        if (cost0 < cost1)
			for (int i = 1; i <= n; ++i) printf("%d%c", ans0[i], " \n"[i == n]);
		else if (cost0 > cost1)
			for (int i = 1; i <= n; ++i) printf("%d%c", ans1[i], " \n"[i == n]);
		else {
			if (!Check(ans0, ans1, n)) std::swap(ans0, ans1);
			for (int i = 1; i <= n; ++i) printf("%d%c", ans0[i], " \n"[i == n]);
		} 
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
    if (isfreopen) freopenI("sequence"), freopenO("sequence");
    if (ismultiple) read(T); else T = 1;
    while (T--) Codespace::Solver(++ Case);
    return 0;
}
