#include <bits/stdc++.h>
std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
int n, LastValue, BeginValue, Delta;
int Query1(int x) {
    static int u;
    printf("> %d\n", x);
    fflush(stdout);
    scanf("%d", &u);
    return u;
}
int Query2(int x) {
    static int u;
    printf("? %d\n", x);
    fflush(stdout);
    scanf("%d", &u);
    return u;
} 
int gcd(int x, int y) {return !y ? x : gcd(y, x % y);}
signed main() {
    scanf("%d", &n);
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (Query1(mid)) l = mid;
        else r = mid - 1;
    }
    std::uniform_int_distribution<int> random(1, n);
    LastValue = l + 1; Delta = LastValue - Query2(random(gen));
    std::vector<int> array;
    for (int i = 1; i <= 25; ++i) array.emplace_back(Query2(random(gen)));
    std::sort(array.begin(), array.end());
    array.erase(std::unique(array.begin(), array.end()), array.end());
    Delta = array[1] - array[0];
    for (int i = 1; i < (int)array.size() - 1; ++i) Delta = gcd(Delta, array[i + 1] - array[i]);
    printf("! %d %d\n", BeginValue = LastValue - (n - 1) * Delta, Delta);
    return 0;
}