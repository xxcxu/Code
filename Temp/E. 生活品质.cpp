# include <bits/stdc++.h>

static const int N = 1005;

FILE *fin, *fout, *ferr;
int r, c, w, h;
int a[N][N], b[N][N], s[N][N];

int ask(int x_1, int y_1, int x_2, int y_2) {
    return s[x_2][y_2] - s[x_1 - 1][y_2] - s[x_2][y_1 - 1] + s[x_1 - 1][y_1 - 1]; 
}

bool check(int x) {
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j) {
            if (a[i][j] < x) b[i][j] = -1;
            if (a[i][j] == x) b[i][j] = 0;
            if (a[i][j] > x) b[i][j] = 1;
        }

    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            s[i][j] = s[i - 1][j] + s[i][j - 1] + b[i][j] - s[i - 1][j - 1];

    for (int i = 1; i + h - 1 <= r; ++i)
        for (int j = 1; j + w - 1 <= c; ++j)
            if (ask(i, j, i + h - 1, j + w - 1) <= 0)
                return true;
    return false;
}

signed main() {
    fin = stdin;
    fout = stdout;
    ferr = stderr;
    // fin = fopen("Input.txt", "r");
    // fout = fopen("Output.txt", "w+");
    // ferr = fopen("Debug.txt", "w+");

    fscanf(fin, "%d%d%d%d", &r, &c, &h, &w);
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            fscanf(fin, "%d", a[i] + j);

    int L = 1, R = r * c, ans;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (check(mid))
            R = mid - 1, ans = mid;
        else
            L = mid + 1;
    }
    fprintf(fout, "%d\n", ans);
    return 0;
}