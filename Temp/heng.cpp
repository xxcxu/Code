#include <bits/stdc++.h>
using pcc = std::pair<char, char>;
static constexpr int N = 1e6 + 5, M = 62, K = 256, P = 998244353;

int n, a[N], sum[N], tot[N], base[K], table[K];
int cnt[N][M], sum1[N][M], sum2[N][M];
int ABA[M][M], BA[M][M];
char s[N];

int add(int x, int y) {return x + y >= P ? x + y - P : x + y;}
void cadd(int &x, int y) {x = add(x, y);}
int mul(int x, int y) {return 1ll * x * y % P;}
void cmul(int &x, int y) {x = mul(x, y);}

int dynamic() {
    int ans = 0;
    for (int i = 1; i + 2 <= n; ++i) {
        for (int j = 0; j < 62; ++j) {
            cadd(ABA[a[i]][j], BA[j][a[i]]);
            cadd(BA[a[i]][j], tot[j]);
        }
        ++ tot[a[i]];
        for (int j = 0; j < 62; ++j) {
            if (j == a[i]) continue;
            int redius = sum[i + 1];
            cadd(redius, P - sum1[i + 1][a[i]]);
            cadd(redius, P - sum1[i + 1][j]);
            cadd(redius, P - sum2[i + 1][a[i]]);
            cadd(redius, P - sum2[i + 1][j]);
            cadd(redius, mul(cnt[i + 1][a[i]], cnt[i + 1][j]));
            cadd(ans, mul(redius, ABA[j][a[i]]));
        }
    } return ans;
}

void solve() {
    scanf("%s", s + 1); n = std::strlen(s + 1);
    for (int i = 1; i <= n; ++i) a[i] = table[(int)s[i]];
    
    for (int i = 1; i <= n; ++i) sum[i] = 0;
    for (int i = 0; i < 62; ++i) tot[i] = 0;
    for (int i = 0; i < 62; ++i) cnt[n + 1][i] = 0;
    for (int i = 0; i < 62; ++i) sum1[n + 1][i] = 0;
    for (int i = 0; i < 62; ++i) sum2[n + 1][i] = 0;
    for (int i = 0; i < 62; ++i) for (int j = 0; j < 62; ++j) ABA[i][j] = 0;
    for (int i = 0; i < 62; ++i) for (int j = 0; j < 62; ++j) BA[i][j] = 0;

    for (int i = n; i >= 1; --i) {
        std::memcpy(cnt[i], cnt[i + 1], 62 * sizeof(int));
        std::memcpy(sum1[i], sum1[i + 1], 62 * sizeof(int));
        std::memcpy(sum2[i], sum2[i + 1], 62 * sizeof(int));
        ++ cnt[i][a[i]];
        for (int j = 0; j < 62; ++j) {
            if (a[i] == j) continue;
            cadd(sum1[i][a[i]], cnt[i + 1][j]);
            cadd(sum2[i][j], cnt[i + 1][j]);
        }
        for (int j = 0; j < 62; ++j) cadd(sum[i], sum1[i][j]);
    }
    printf("%d\n", dynamic());
}

signed main() {
    freopen("heng.in", "r", stdin);
    freopen("heng.out", "w", stdout);
    for (int i = 0; i < 26; ++i) table['a' + i] = i, base[i] = 'a' + i;
    for (int i = 26; i < 52; ++i) table['A' + i - 26] = i, base[i] = 'A' + i - 26;
    for (int i = 52; i < 62; ++i) table['0' + i - 52] = i, base[i] = '0' + i - 52;
    int t; scanf("%d", &t);
    while (t--) solve();
}