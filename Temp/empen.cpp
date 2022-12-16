#include <bits/stdc++.h>
static constexpr int N = 5e5 + 5;
int n, k, cnt;
char str[N];
class node {
    public: char op; int len;
    public: node(): op('\0'), len(0) {}
} a[N];
bool cmp(const node &a, const node &b) {
    if (a.op == 'R') return b.op == 'S';
    if (a.op == 'S') return b.op == 'P';
    if (a.op == 'P') return b.op == 'R';
}
void swap(node &a, node &b) {
    node tmp;
    tmp.op = a.op; tmp.len = a.len;
    a.op = b.op; a.len = b.len;
    b.op = tmp.op; b.len = tmp.len;
}
signed main() {
    freopen("empen.in", "r", stdin);
    freopen("empen.out", "w", stdout);
    scanf("%d%d", &n, &k);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i) {
        if (str[i] != str[i - 1]) 
            a[++ cnt].op = str[i];
        ++ a[cnt].len;
    }
    for (int i = 1; i <= cnt; ++i) {
        if (a[i].op == a[i + 1].op) a[i + 1].len += a[i].len;
        else {
            if (a[i].len > k) {
                for (int j = 1; j <= a[i].len - k; ++j) putchar(a[i].op); 
                a[i].len = k;
            }
            if (cmp(a[i], a[i + 1])) swap(a[i], a[i + 1]);
            for (int j = 1; j <= a[i].len; ++j) putchar(a[i].op);
        }
    } return 0;
}