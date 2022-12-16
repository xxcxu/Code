#include <bits/stdc++.h>
using ll = long long;
ll n, l, r;
int k;
int query(ll l, ll r) {
	static char s[5];
	printf("%lld %lld\n", l, r);
	fflush(stdout);
	scanf("%s", s + 1);
	return s[1] == 'Y';
}
signed main() {
	scanf("%lld%d", &n, &k); l = 1, r = n;
	std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
	while (true) {
		while (r - l > 50) {
			ll mid = (l + r) >> 1;
			if (query(l, mid)) r = mid;
			else l = mid + 1;
			l = std::max(1ll, l - k), r = std::min(n, r + k);
		}
		std::uniform_int_distribution<ll> random(l, r);
		ll p = random(gen) ;
		if (query(p, p)) return 0;
		l = std::max(1ll, l - k), r = std::min(n, r + k);
	}
}