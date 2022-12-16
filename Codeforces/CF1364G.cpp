#include <bits/stdc++.h>
std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
int n, k;
int Query(int l1, int r1, int l2, int r2) {
    printf("? %d %d\n", r1 - l1 + 1, r2 - l2 + 1);
    for (int i = l1; i <= r1; ++i) printf("%d ", i); puts("");
    for (int i = l2; i <= r2; ++i) printf("%d ", i); puts("");
    fflush(stdout);
    char c[10];
    scanf("%s", c + 1);
    assert(c[1] != 'W');
    if (c[1] == 'F') return -1;
    if (c[1] == 'S') return 1;
    if (c[1] == 'E') return 0;
    return -2;
}
int FindRock() {
    std::uniform_int_distribution<int> random(1, n);
    int p = 1;
    for (int i = 1; i <= 20; ++i) {
        static int q;
        do {q = random(gen);} while (q == p);
        if (Query(p, p, q, q) == 1) p = q;
    }
    return p;
}
int Ask(int l, int r) {
    int L = l, R = r, ans;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (Query(1, mid - l + 1, l, mid) != -1) L = mid + 1;
        else R = mid - 1, ans = mid;
    }
    return ans;
}
int FirstGift(int x) {
    if (x != 1) return 1;
    int l = 1, r = 1;
    while (1) {
        if (2 * r > n) return Ask(r + 1, n);
        int res = Query(l, r, r + 1, 2 * r);
        if (res == -1) return Ask(r + 1, 2 * r);
        r *= 2;
    }
}
void Solve() {
    scanf("%d%d", &n, &k);
    if (n == 1) return printf("! %d\n", 1), void();
    int p = FindRock();
    printf("! %d\n", FirstGift(p));
    fflush(stdout);
}
signed main() {
    int t; scanf("%d", &t);
    while (t--) Solve();
}
