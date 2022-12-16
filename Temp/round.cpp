#include <bits/stdc++.h>
static constexpr int N = 1e6 + 5;
int n, q;
signed main() {
    // freopen("round.in", "r", stdin);
    // freopen("round.out", "w", stdout);
    scanf("%d%d", &n, &q);
    while (q--) {
        static int s, l;
        scanf("%d%d", &s, &l);
        int p = s;
        int IDSum = 0, LivePeople = n, Interval = 2;
         while (1) {
            if (LivePeople >= l && (LivePeople + 1) / 2 < l || (LivePeople == l && l == 1)) {
                printf("%d\n", p);
                IDSum = Interval * l * (l - 1) / 2 + p * l;
                break;
            }
            p = (p + LivePeople / 2 * Interval - 1) % n + 1;
            LivePeople = (LivePeople + 1) / 2;
            Interval = Interval * 2;
            printf("%d %d %d\n", p, LivePeople, Interval);
        }
        printf("%d\n", IDSum);
    } return 0;
}