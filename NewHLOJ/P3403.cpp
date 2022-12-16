#include <bits/stdc++.h>
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
int t, n;
signed main(){
	read(t);
	while (t --) {
        read(n);
        puts(n % 4 ? "A" : "B");
    } return 0;
}