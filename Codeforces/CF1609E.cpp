#include <bits/stdc++.h>
static constexpr int N = 1e5 + 5;
class Matrix {
	private: int n, m;
	public: std::vector<std::vector<int>> a;
	public: Matrix(int n = 0, int m = 0, int p = 0): n(n), m(m) {
		a.resize(n, std::vector<int>(m, 0x3f3f3f3f));
		if (p) {
			assert(n == m);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					a[i][j] = (i == j);
		}
	}
	public: std::vector<int>& operator [] (int x) & {return a[x];}
	public: const std::vector<int>& operator[](int x) const& {return a[x];}
	public: friend Matrix operator * (const Matrix &a, const Matrix &b) {
		Matrix ans = Matrix(a.n, b.m);
		for (int i = 0; i < a.n; ++i)
			for (int j = 0; j < b.m; ++j)
				for (int k = 0; k < a.m; ++k)
					ans[i][j] = std::min(ans[i][j], a[i][k] + b[k][j]);
		return ans;
	}
	public: auto Unit() -> void {
		assert(n == m);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				a[i][j] = (i == j);
		return void();
	}
	public: friend Matrix operator ^ (Matrix a, int k) {
		Matrix ans = Matrix(a.n, a.m, 1);
		for (; k; k >>= 1, a = a * a)
			if (k & 1) ans = ans * a;
		return ans;
	}
};
int n, q; char c, str[N];
class SegmentTree {
private: Matrix tr[N << 2];
	#define ls (rt << 1)
	#define rs (rt << 1 | 1)
	public: auto Make(char ch) -> Matrix {
		Matrix TreeNode = Matrix(3, 3);
		TreeNode[0][0] = ch == 'a';
		TreeNode[0][1] = ch != 'a';
		TreeNode[1][1] = ch == 'b';
		TreeNode[1][2] = ch != 'b';
		TreeNode[2][2] = ch == 'c';
		return TreeNode;
	}
	private: auto Pushup(int rt) -> void {tr[rt] = tr[ls] * tr[rs];}
	public: auto Build(int rt, int l, int r) -> void {
		tr[rt] = Matrix(3, 3);
		if (l == r) return void(tr[rt] = Make(str[l]));
		int mid = (l + r) >> 1;
		Build(ls, l, mid); Build(rs, mid + 1, r);
		Pushup(rt);
	}
	public: auto Update(int rt, int l, int r, int x, Matrix v) -> void {
		if (l == r) return void(tr[rt] = v);
		int mid = (l + r) >> 1;
		if (x <= mid) Update(ls, l, mid, x, v);
		else Update(rs, mid + 1, r, x, v);
		Pushup(rt);
	}
	public: auto Query(int rt, int l, int r, int ql, int qr) -> Matrix {
		if (ql <= l && r <= qr) return tr[rt];
		int mid = (l + r) >> 1; Matrix ans(3, 3, 1);
		if (ql <= mid) ans = ans * Query(ls, l, mid, ql, qr);
		if (qr > mid) ans = ans * Query(rs, mid + 1, r, ql, qr);
		return ans;
	}
	#undef ls
	#undef rs
} Tree;
signed main() {
	scanf("%d %d %s", &n, &q, str + 1); Tree.Build(1, 1, n);
	for (int i = 1, x; i <= q; ++i) {
		scanf("%d %c", &x, &c);
		Tree.Update(1, 1, n, x, Tree.Make(c));
		Matrix ans = Matrix(3, 3); ans[0][0] = 0; 
		ans = ans * Tree.Query(1, 1, n, 1, n);
		printf("%d\n", std::min({ans[0][0], ans[0][1], ans[0][2]}));
	} return 0;
}