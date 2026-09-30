#include "../utilities/template.h"
#include "../../content/math/BerlekampMassey.h"

int main() {
	mt19937 rng(3);
	assert(berlekampMassey({}).empty());
	assert(berlekampMassey({0, 0, 0}).empty());
	assert((berlekampMassey({0, 1, 1, 3, 5, 11}) == vector<ll>{1, 2}));
	rep(it,0,3000) {
		int d = 1 + rng() % 8;
		vector<ll> tr(d), s(2 * d + 10);
		for (auto& t : tr) t = rng() % mod;
		rep(i,0,d) s[i] = rng() % mod;
		rep(i,d,sz(s)) {
			s[i] = 0;
			rep(j,0,d) s[i] = (s[i] + tr[j] * s[i - 1 - j]) % mod;
		}
		vector<ll> c = berlekampMassey(vector<ll>(s.begin(), s.begin() + 2 * d));
		assert(sz(c) <= d);
		// recovered recurrence must generate the whole sequence
		rep(i,sz(c),sz(s)) {
			ll v = 0;
			rep(j,0,sz(c)) v = (v + c[j] * s[i - 1 - j]) % mod;
			assert(v == s[i]);
		}
	}
	cout << "Tests passed!" << endl;
}
