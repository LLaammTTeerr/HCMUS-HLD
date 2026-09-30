#include "../utilities/template.h"
#include "../../content/various/BigNum.h"

typedef __int128 LL;
string str128(LL x) {
	if (x == 0) return "0";
	string s;
	for (; x; x /= 10) s += char('0' + (int)(x % 10));
	reverse(all(s)); return s;
}

int main() {
	mt19937_64 rng(42);
	auto rnd128 = [&]() -> LL {
		int bits = (int)(rng() % 127);
		LL x = ((LL)rng() << 64 | rng()) & (((LL)1 << bits) - 1);
		return x;
	};
	// Exact checks against __int128 (values < 2^63 so products fit).
	rep(it,0,200000) {
		ll x = (ll)(rng() >> (1 + rng() % 63)), y = (ll)(rng() >> (1 + rng() % 63));
		Big a(x), b(str128(y));
		assert(a.str() == str128(x) && b.str() == str128(y));
		assert((a < b) == (x < y) && (a == b) == (x == y));
		assert((a + b).str() == str128((LL)x + y));
		if (x >= y) assert((a - b).str() == str128((LL)x - y));
		assert((a * b).str() == str128((LL)x * y));
		ll m = 1 + (ll)(rng() % 9000000000ULL);
		assert((a * m).str() == str128((LL)x * m));
		auto [q, r] = a.divmod(m);
		assert(q.str() == str128(x / m) && r == x % m);
		if (y) {
			auto [q2, r2] = a.divmod(b);
			assert(q2.str() == str128(x / y) && r2.str() == str128(x % y));
		}
		LL z = rnd128();
		assert(Big(str128(z)).str() == str128(z));
	}
	// Leading zeros and zero.
	assert(Big("000000000000000123").str() == "123");
	assert(Big("0000").str() == "0" && Big("0") == Big(0));
	// Identities on large random numbers.
	auto big = [&](int n) {
		string s(n, '0');
		for (char& c : s) c = char('0' + rng() % 10);
		return Big(s);
	};
	rep(it,0,300) {
		Big a = big(1 + (int)(rng() % 300)), b = big(1 + (int)(rng() % 150));
		assert(a + b - b == a);
		assert((a + b) * b == a * b + b * b);
		if (b == Big(0)) continue;
		auto [q, r] = a.divmod(b);
		assert(r < b && q * b + r == a);
	}
	cout << "Tests passed!" << endl;
}
