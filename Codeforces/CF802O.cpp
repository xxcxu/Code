#include <bits/stdc++.h>
#define int long long
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
using pii = std::pair<int, int>;
static constexpr int N = 5e5 + 5;
int n, k;
int a[N], b[N];
signed main() {
    read(n, k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) read(b[i]);
    int l = 0, r = 2e9;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int cnt = 0, tot = 0;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
        for (int i = 1; i <= n; ++i) {
            q.emplace(a[i] - mid, 0);
            auto m = q.top();
            int val = b[i] + m.first;
            if (val < 0) {
                tot += val;
                if (!m.second) ++ cnt;
                q.pop();
                q.emplace(-b[i], 1);                
            }
        }
        if (cnt == k) return printf("%lld\n", tot + k * mid), 0;
        else if (cnt < k) l = mid + 1;
        else r = mid - 1;
    }
}