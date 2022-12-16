#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e5 + 5;
int n, cnt[N], s[N];
std::vector<int> id;
auto main() -> decltype(0) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);
    std::cin >> n;
    std::vector<std::string> str(n);
    std::string t = "";
    for (int i = 0; i < n; ++i) std::cin >> str[i];
    for (int i = 0; i < n; ++i) {
        for (auto j : str[i]) 
            if (j == 'X') ++ cnt[i];
            else s[i] += (j - '0');
        if (cnt[i] and s[i]) id.emplace_back(i);
    }
    std::sort(id.begin(), id.end(), [&](int a, int b) {return cnt[a] * s[b] > cnt[b] * s[a];});
    for (int i = 0; i < n; ++i) if (!s[i]) t = t + str[i];
    for (int i = 0; i < (int)id.size(); ++i) t = t + str[id[i]];
    for (int i = 0; i < n; ++i) if (!cnt[i]) t = t + str[i];
    int ans = 0, sum = 0;
    for (int i = (int)t.size() - 1; ~i; --i) {
        if (i == 'X') ans += sum;
        else sum += (i - '0');
    }
    return std::cout << ans << std::endl, 0;
}