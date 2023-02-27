# include <bits/stdc++.h>

using pii = std::pair<int, int>;
using LL = long long;

# define gc getchar
# define eb emplace_back
# define ep emplace

int read() {
	int x = 0, f = 0; char ch = gc();
	for (; !isdigit(ch); ch = gc()) f ^= (ch == '-');
	for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
	return f ? -x : x;
}

static const int N = 1005;

int n, c[N], d[N];
int leaf[N];
std::vector<int> e[N];

void dfs(int x) {
    int cnt[3] = {0, 0, 0};
    if (leaf[x]) return void();
    for (int y : e[x]) {
        dfs(y);
        ++ cnt[c[y]];
    }
    if (cnt[2] == cnt[1]) c[x] = 0; // First win
    if (cnt[2] <  cnt[1]) c[x] = 1; // Bob
    if (cnt[2] >  cnt[1]) c[x] = 2; // Alice
}

signed main() {
    // freopen("color.in", "r", stdin);
    // freopen("color.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; ++i) {
        c[i] = read();
        if (c[i] <= 0) {leaf[i] = 1, c[i] = -c[i]; continue;}
        for (int j = 1; j <= c[i]; ++j) e[i].eb(read());
    }
    dfs(1); int win;
    if (c[1] == 1) win = 1;
    if (c[1] != 1) win = 2;
    puts(win == 1 ? "Bob" : "Alice");
    if (win == 2) {
        std::vector<int> v;
        for (int i = 1; i <= n; ++i)
            if (leaf[i] && !c[i]) {
                c[i] = 2, dfs(1);
                if (c[1] == 2) v.eb(i);
                c[i] = 0;
            }
        printf("%d\n", (int)v.size());
        for (int p : v) printf("%d ", p);
    }
    return 0;
}
