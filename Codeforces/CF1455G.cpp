#include <bits/stdc++.h>
#define int long long
template<typename DataType>
DataType read() {
    DataType t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}
#define eb emplace_back
#define pb push_back
#define ep emplace
#define pu push
#define begin(x) (*x.begin())
static constexpr int N = 2e5 + 5;
int n, s, res, f[N], t[N], v[N], p[N];
int d[N];
std::vector<int> a[N];
std::map<int, int> dp[N];
std::multiset<int> mn[N];
void Dfs(int x) {
    mn[x].ep(dp[x][p[x]] = 0);
    for (auto to : a[x]) {
        if (t[to] == 1) {
            if (p[to] != s) {
                if (dp[x].count(p[to])) {
                    int tmp = dp[x][p[to]];
                    dp[x][p[to]] = begin(mn[x]) - v[to];
                    mn[x].erase(mn[x].find(tmp));
                } else
                    dp[x][p[to]] = begin(mn[x]) - v[to];
                mn[x].ep(dp[x][p[to]]);
            }
            d[x] += v[to];
        } else if (dp[x].count(p[to])) {
            Dfs(to);
            int tmp = dp[x][p[to]] + d[to];
            if (dp[to].size() <= dp[x].size()) {
                for (auto [id, cost] : dp[to]) {
                    if (!dp[x].count(id)) dp[x][id] = tmp + cost;
                    else {
                        mn[x].erase(mn[x].find(dp[x][id]));
                        if (id == p[to]) dp[x][id] = tmp + cost;
                        else dp[x][id] = std::min(dp[x][id], tmp + cost);
                    }
                    mn[x].ep(dp[x][id]);
                }
            } else {
                d[x] += tmp;
                for (auto [id, cost] : dp[x]) {
                    if (!dp[to].count(id)) dp[to][id] = cost - tmp;
                    else {
                        mn[to].erase(mn[to].find(dp[to][id]));
                        if (id != p[to]) dp[to][id] = std::min(dp[to][id], cost - tmp);
                    }
                    mn[to].ep(dp[to][id]);
                }
                std::swap(dp[x], dp[to]);
                std::swap(mn[x], mn[to]);
			}
		}
	}
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    std::cin >> n >> s;
    for (int i = 1; i <= n; ++i) {
        static std::string opt;
        std::cin >> opt;
        if (opt[0] == 's') {
            a[res].eb(i);
            t[i] = 1;
            std::cin >> p[i] >> v[i];
        } else if (opt[0] == 'i') {
            a[res].eb(i);
            t[i] = 2;
            std::cin >> p[i];
            f[i] = res;
            res = i;
        } else res = f[res];
    }
    Dfs(0);
    std::cout << d[0] + begin(mn[0]) << std::endl;
    return 0;
}
/*
9 200
if 0
    set 5 5
    if 5
        set 100 13
    end
    if 100
        set 200 1
    end
end

9 200
if 0
set 5 5
if 5
set 100 13
end
if 100
set 200 1
end
end
*/