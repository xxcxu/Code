#include <bits/stdc++.h>
FILE *fin, *fout, *ferr;
static const int N = 85;
int n, m, ans;
char s[N], t[N];
int dp1[N][N], dp2[N][N][N];
int LCS2(int l1, int r1, int l2, int r2)
{
    for (int i = l1 - 1; i <= r1 + 1; ++i)
        for (int j = l2 - 1; j <= r2 + 1; ++j)
            dp1[i][j] = 0;
    for (int i = l1; i <= r1; ++i)
        for (int j = l2; j <= r2; ++j)
        {
            dp1[i][j] = std::max({dp1[i][j], dp1[i - 1][j], dp1[i][j - 1]});
            dp1[i][j] = std::max(dp1[i][j], dp1[i - 1][j - 1] + (s[i] == s[j]));
        }
    return dp1[r1][r2];
}
int LCS3(int l1, int r1, int l2, int r2, int l3, int r3)
{
    for (int i = l1 - 1; i <= r1 + 1; ++i)
        for (int j = l2 - 1; j <= r2 + 1; ++j)
            for (int k = l3 - 1; k <= r3 + 1; ++k)
                dp2[i][j][k] = 0;
    for (int i = l1; i <= r1; ++i)
        for (int j = l2; j <= r2; ++j)
            for (int k = l3; k <= r3; ++k)
            {
                dp2[i][j][k] = std::max({dp2[i][j][k], dp2[i - 1][j][k], dp2[i][j - 1][k], dp2[i][j][k - 1]});
                dp2[i][j][k] = std::max(dp2[i][j][k], dp2[i - 1][j - 1][k - 1] + (s[i] == s[j] && s[j] == s[k]));
            }
    return dp2[r1][r2][r3];
}
int calc()
{
    int ans = 0;
    for (int i = 1, j = 0; i <= n; ++i)
    {
        if (j < m && s[i] == t[j + 1])
        {
            ++j;
            if (j == m)
                j = 0, ++ans;
        }
    }
    return ans > 1 ? ans * m : 0;
}

signed main()
{
    // fin = fopen("Input.txt", "r");
    // fout = fopen("Output.txt", "w+");
    // ferr = fopen("Debug.txt", "w+");
    fin = stdin;
    fout = stdout;
    ferr = stderr;
    fscanf(fin, "%s", s + 1);
    n = std::strlen(s + 1);
    for (int i = 1; i < n; ++i)
        ans = std::max(ans, 2 * LCS2(1, i, i + 1, n));
    for (int i = 1; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            ans = std::max(ans, 3 * LCS3(1, i, i + 1, j, j + 1, n));
    for (int i = 1; i <= n; ++i)
        for (int S = 0; S < (1 << 16); ++S)
            if (S >> 0 & 1)
            {
                m = 0;
                for (int j = 0; j < 16 && i + j <= n; ++j)
                    if (S >> j & 1)
                        t[++m] = s[i + j];
                ans = std::max(ans, calc());
            }
    return fprintf(fout, "%d\n", ans), 0;
}