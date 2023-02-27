#include <bits/stdc++.h>
#define eb emplace_back
static const int N = 30005, M = 300005;
int n, max, ans, tot, len[N], in[30];
int f[N * 64], ch[N * 64][26];
std::string s[N];
bool isans[N];
std::vector<char> alp[M];
std::vector<int> e[30];
void build(int p, int x) {
    for (int i = 0; i < len[x]; ++i) {
        int c = s[x][i] - 'a';
        if (!ch[p][c]) ch[p][c] = ++ tot;
        p = ch[p][c];
    }
    ++ f[p];
}
void search(int p, int x) {
    for (int i = 0; i < len[x]; ++i) {
        int c = s[x][i] - 'a';
        for (int j = 0; j < 26; ++j) if (ch[p][j] && j != c) e[c].eb(j), ++ in[j];
        p = ch[p][c];
    }
}
bool issuf(int p, int x) {
    for (int i = 0; i < len[x]; ++i) {
        int c = s[x][i] - 'a';
        if (f[p]) return true;
        p = ch[p][c];
    } return false;
}
bool topsort() {
    std::queue<int> q;
    for (int i = 0; i < 26; ++i) if (!in[i]) q.emplace(i);
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int y : e[x]) if (!(--in[y])) q.emplace(y);
    }
    for (int i = 0; i < 26; ++i) if (in[i]) return false;
    return true;
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> s[i];
    for (int i = 1; i <= n; ++i) {
        len[i] = s[i].length();
        max = std::max(max, len[i]);
        for (int j = 0; j < len[i]; ++j) alp[j].eb(s[i][j]);
    }
    for (int i = 1; i <= n; ++i) build(0, i);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 26; ++j) e[j].clear();
        for (int j = 0; j < 26; ++j) in[j] = 0;
        search(0, i);
        isans[i] = topsort() && (!issuf(0, i));
    }
    for (int i = 1; i <= n; ++i) ans += isans[i];
    std::cout << ans << std::endl;
    for (int i = 1; i <= n; ++i) if (isans[i]) std::cout << s[i] << std::endl;
    // return 0;
}