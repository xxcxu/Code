#include <bits/stdc++.h>

static constexpr int N = 1e5 + 5;

int n, tot;
int cnta, cntb, cntc;
bool flag1;
char s[N * 2];

class node {
    public: char op; int len;
    public: node(char op = '\0', int len = 0):
        op(op), len(len) {}
} p[N];

void subtask1() {
    for (int i = 1; i <= 2 * n; ++i) {
        if (s[i] != s[i - 1]) p[++ tot] = node(s[i], 0);
        ++ p[tot].len;
    }
    if (tot == 1) puts("NO");
    else if (tot == 2) {
        if (p[1].len != p[2].len) puts("NO");
        else {
            puts("YES");
            for (int i = 1, j = 1, k = p[1].len + 1; i <= n; ++i)
                printf("%d %d\n", j ++, k ++);
        }
    } else {
        int AB = n - cntc;
        int BC = cntb - AB;
        int AC = cnta - AB;
        if (AB < 0 || BC < 0 || AC < 0) puts("NO");
        else {
            puts("YES");
            for (int i = 1; i <= AB; ++i) printf("%d %d\n", i, p[1].len + i);
            for (int i = 1; i <= BC; ++i) printf("%d %d\n", p[1].len + AB + i, p[1].len + p[2].len + i);
            for (int i = 1; i <= AC; ++i) printf("%d %d\n", AB + i, p[1].len + p[2].len + BC + i);
        }
    }
}

void subtask2() {
    using pii = std::pair<int, int>;
    #define eb emplace_back
    
    static int cnt = 0;
    static pii pair[N];

    if (cnta != cntb) puts("NO");
    else {
        std::vector<int> posa, posb;
        for (int i = 1; i <= n * 2; ++i)
            if (s[i] == 'A') posa.eb(i);
            else if (s[i] == 'B') posb.eb(i);
        int j = 0;
        for (auto i : posa) 
            if (posb[j] < i) return puts("NO"), void(); 
            else pair[++ cnt] = pii(i, posb[j ++]);
        puts("YES");
        for (int i = 1; i <= n; ++i)
            printf("%d %d\n", pair[i].first, pair[i].second);
    }
    #undef eb
}

void subtask3() {
    #define eb emplace_back
    std::vector<std::pair<int, int>> ans;
    int AB = n - cntc;
    int AC = cnta - AB;
    int BC = cntb - AB;
    if (AB < 0 || AC < 0 || BC < 0) return puts("NO"), void();

    std::vector<int> bpos;
    for (int i = 1; i <= n * 2; ++i) if (s[i] == 'B') bpos.eb(i);
    
    for (int i = 0, j = 1; i < BC; ++i) {
        for (; j <= n * 2; ++j) if (s[j] == 'C' && j > bpos[i]) break;
        if (j <= n * 2) ans.eb(bpos[i], j), s[j ++] = '\0';
        else return puts("NO"), void();
    }
    
    for (int i = cntb - 1, j = n * 2; i >= BC; --i) {
        for (; j >= 1; --j) if (s[j] == 'A' && j < bpos[i]) break;
        if (j) ans.eb(j, bpos[i]), s[j --] = '\0';
        else return puts("NO"), void();
    }

    std::stack<int> st;
    for (int i = 1; i <= n * 2; ++i) {
        if (s[i] == 'A') st.emplace(i);
        else if (s[i] == 'C')
            if (!st.size()) return puts("NO"), void();
            else ans.eb(st.top(), i), st.pop();
    }
    
    puts("YES");
	for (auto it : ans) printf("%d %d\n", it.first, it.second);
    #undef eb
}

signed main() {
    freopen("subsequent.in", "r", stdin);
    freopen("subsequent.out", "w", stdout);
    scanf("%d%s", &n, s + 1); flag1 = true;
    for (int i = 1; i <= 2 * n; ++i) {
        if (s[i] == 'A') ++ cnta;
        if (s[i] == 'B') ++ cntb;
        if (s[i] == 'C') ++ cntc;
        if (i > 1) flag1 &= (s[i] >= s[i - 1]);
    }
    if (flag1) subtask1();
    else if (!cntc) subtask2();
    else subtask3();
    return 0;
}