# include <bits/stdc++.h>

static const int N = 2005;

int n, P, f[N];
FILE *fin, *fout, *ferr;

int inc(int x, int y) { return (x + y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }

void init(int n) {
	f[0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = i; k <= n; ++k)
				f[k] = inc(f[k], f[k - i]);
	return void();
}

void solve0() {
	fscanf(fin, "%d", &n);
	int a, b;
	a = b = (int)std::sqrt(n);
    while (a * b < n)
    {
        ++ a;
		std::swap(a, b);
    }
    fprintf(fout, "%d %d\n", a, b);
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			fprintf(fout, "%c", ".#"[i * b + j < n]);
		}
		fputs("\n", fout);
	}
}

void solve1() {
	fscanf(fin, "%d", &n);
	int a, b;
	a = b = (int)std::sqrt(n);
	while (a * b < n) {
		++ a;
		std::swap(a, b);
	}
	int ans = 0;
	if (a == b) ans = -f[a * b - n];
	while (a * b >= n) {
		ans = inc(ans, mul(f[a * b - n], 2));
		-- a;
		++ b;
	}
	fprintf(fout, "%d %d\n", 2 * (a + b), ans);
}
signed main() {
    // fin = stdin;
    // fout = stdout;
    // ferr = stderr;
    fin = fopen("Input.txt", "r");
    fout = fopen("Output.txt", "w+");
    ferr = fopen("Debug.txt", "w+");
    int t, opt;
    fscanf(fin, "%d%d", &t, &opt);
    if (opt == 2) fscanf(fin, "%d", &P);
	if (opt == 2) init(N - 1);
	while (t--)
		if (opt == 1) solve0();
		else solve1();
	return 0;
}