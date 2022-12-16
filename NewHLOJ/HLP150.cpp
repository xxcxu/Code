#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 100, mod = 998244353;
int n, k, r;
int a[N];
int dp[N][N];
int main()
{
    int _;
    scanf("%d", &_);
    while (_--)
    {
        scanf("%d%d%d", &n, &k, &r);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        for (int i = 0; i <= n; i++)
            memset(dp[i], 0, (k + 1) * sizeof(int));
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++)
        {
            int pos = i - 1;
            for (pos = i - 1; pos > 0; pos--)
                if (a[i] - a[pos] >= r)
                    break;
            for (int k = 1; k <= i; k++)
            {
                if ((i - pos - 1) < k)
                    dp[i][k] = 1ll * dp[i - 1][k] * (k - (i - pos - 1)) % mod;
                dp[i][k] = (dp[i][k] + dp[i - 1][k - 1]) % mod;
            }
        }
        printf("%d\n", dp[n][k]);
    }
    return 0;
}