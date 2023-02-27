#include <bits/stdc++.h>

const int N = 1000005, inf = 0x3f3f3f3f, inf2 = 0xf3f3f3f3;
int n, a[N], b[N];
int f[N][2][2], g[N][2][2];
FILE *fin, *fout, *ferr;

void cmax(int &f, int &g, int val, int from) {
    if (val > f)
        f = val, g = from;
    return void();
}
void cmin(int &f, int &g, int val, int from) {
    if (val < f)
        f = val, g = from;
    return void();
}

void solve() {
    fscanf(fin, "%d", &n);
    for (int i = 1; i <= n; ++i) fscanf(fin, "%d", a + i);
    f[1][0][0] = f[1][1][0] = inf;
    f[1][0][1] = f[1][1][1] = inf2;
    for (int i = 2; i <= n; ++i) {
        f[i][0][0] = f[i][1][0] = inf2;
        f[i][0][1] = f[i][1][1] = inf;
    }
    for (int i = 2; i <= n; ++i) {
        if (f[i - 1][0][0] >= 1) {
            if (a[i] < a[i - 1]) cmax(f[i][0][0], g[i][0][0], f[i - 1][0][0], 0);
            cmax(f[i][1][0], g[i][1][0], f[i - 1][0][0], 0);
            if (a[i] < f[i - 1][0][0]) cmax(f[i][0][0], g[i][0][0], a[i - 1], 1);
            cmax(f[i][1][0], g[i][1][0], a[i - 1], 1);
        }
        if (f[i - 1][1][0] >= 1) {
            if (a[i - 1] < a[i]) cmax(f[i][1][0], g[i][1][0], f[i - 1][1][0], 4);
            if (f[i - 1][1][0] > a[i]) cmin(f[i][0][1], g[i][0][1], a[i - 1], 5);
            cmin(f[i][1][1],g[i][1][1], a[i - 1], 5);
        }
        if (f[i - 1][0][1] <= n) {
            if (a[i - 1] > a[i]) cmin(f[i][0][1], g[i][0][1], f[i - 1][0][1], 2);
            cmin(f[i][1][1], g[i][1][1], f[i - 1][0][1], 2);
            if (f[i - 1][0][1] < a[i]) cmax(f[i][1][0], g[i][1][0], a[i - 1], 3);
        }
        if (f[i - 1][1][1] <= n) {
            if (a[i - 1] < a[i]) cmin(f[i][1][1], g[i][1][1], f[i - 1][1][1], 6);
            if (f[i - 1][1][1] < a[i]) cmin(f[i][1][1], g[i][1][1], a[i - 1], 7);
        }
    }
    if (f[n][1][1] > n)
        fputs("NO\n", fout);
    else {
        fputs("YES\n", fout);
        std::vector<int> c[2];
        int j = 1, k = 1, now = 0;  
        for (int i = n; i >= 1; --i) {
            b[i] = a[i];
            int to = g[i][j][k];
            c[now].push_back(i);
            now ^= (to & 1);
            j = (to >> 2) & 1;
            k = (to >> 1) & 1;
        }
        for (int j = 0; j < 2; ++j) {
            std::reverse(c[j].begin(), c[j].end());
            for (int i = 0; i < (int)c[j].size() - 1; ++i)
                if (a[c[j][i]] > a[c[j][i + 1]])
                    b[c[j][i]] = -b[c[j][i]];
                else
                    break;
        }
        for (int i = 1; i <= n; ++i)
            fprintf(fout, "%d%c", b[i], " \n"[i == n]);
    }
    return void();
}

int main() {
    fin = stdin;
    fout = stdout;
    ferr = stderr;
    // fin = fopen("Input.txt", "r");
    // fout = fopen("Output.txt", "w+");
    // ferr = fopen("Debug.txt", "w+");
    int t;
    fscanf(fin, "%d", &t);
    while (t--)
        solve();
    return 0;
}