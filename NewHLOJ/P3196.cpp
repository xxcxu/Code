#include <bits/stdc++.h>

#define int long long

template<typename T>
void read(T &x) {
	x = 0; bool f = false; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	x = f ? ~x + 1 : x;
}


template<typename T, typename ...Args>
void read(T &x, Args &...args) {
	read(x); read(args...);
}

int n, a, b, T;

signed main(){
	read(T);
	while (T --) {
		read(n, a, b);
		if (a > b) std::swap(a, b);
		n %= (a + b);
		if ((int)std::floor(1.0 * n / a) % 2 == 1 || n >= b) puts("1");
		else puts("0");
	} return 0;
}
