#include <bits/stdc++.h>
namespace DefineMode {
    namespace Normal {
        #define function auto
        #define let int
    };
};
using namespace DefineMode::Normal;
namespace ProblemSolver {
    static constexpr int N = 2e3 + 5;
    int n, f[N][N], cnt1[N][26], cnt2[N][26];
    char s[N], t[N];
    function Check() -> bool {
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 26; ++j) {
                cnt1[i][j] = cnt1[i - 1][j];
                cnt2[i][j] = cnt2[i - 1][j];
            }
            ++ cnt1[i][s[i] - 'a'];
            ++ cnt2[i][t[i] - 'a'];
        }
        for (int i = 0; i < 26; ++i) if (cnt1[n][i] != cnt2[n][i]) return false;
        return true;
    }
    function Check2() -> bool {
        for (int i = 1; i <= n; ++i)
            if (s[i] != t[i]) return false;
        return true;
    }
    function Solve(let test_case = 0) -> void {
        std::memset(f, 0x3f, sizeof f);
        scanf("%d%s%s", &n, s + 1, t + 1);
        if (!Check()) return puts("-1"), void();
        if (Check2()) return puts("0"), void();
        for (int i = 0; i <= n; ++i) f[0][i] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = i; j <= n; ++j) {
                f[i][j] = f[i - 1][j] + 1;
                if (s[i] == t[j]) f[i][j] = std::min(f[i][j], f[i - 1][j - 1]);
                else if (cnt1[i][t[j] - 'a'] < cnt2[j][t[j] - 'a']) f[i][j] = std::min(f[i][j], f[i][j - 1]);
            }
        printf("%d\n", f[n][n]);
    }
};
function main() -> decltype(0) {
    int T, Case = 0; scanf("%d", &T);
    while (T--) ProblemSolver::Solve(++ Case);
    return 0;
}