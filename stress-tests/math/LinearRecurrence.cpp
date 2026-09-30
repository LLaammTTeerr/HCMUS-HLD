#include "../utilities/template.h"
#include "../../content/math/LinearRecurrence.h"

int main() {
	mt19937 rng(4);
	assert(linearRec({0, 1}, {1, 1}, 10) == 55);
	rep(it,0,2000) {
		int d = 1 + rng() % 8;
		vector<ll> tr(d), S(d);
		for (auto& t : tr) t = rng() % mod;
		for (auto& t : S) t = rng() % mod;
		vector<ll> s(S);
		int K = 60;
		while (sz(s) < K) {
			ll v = 0;
			rep(j,0,d) v = (v + tr[j] * s[sz(s) - 1 - j]) % mod;
			s.push_back(v);
		}
		rep(q,0,5) {
			int k = (int)(rng() % K);
			assert(linearRec(S, tr, k) == s[k]);
		}
	}
	// large k: Fibonacci via fast doubling
	auto fib = [&](ll n) {
		function<pair<ll,ll>(ll)> go = [&](ll m) -> pair<ll,ll> {
			if (!m) return {0, 1};
			auto [a, b] = go(m / 2);
			ll c = a * ((2 * b - a + mod) % mod) % mod, e = (a * a + b * b) % mod;
			return m % 2 ? make_pair(e, (c + e) % mod) : make_pair(c, e);
		};
		return go(n).first;
	};
	for (ll k : {1000000000000LL, 123456789012345678LL, 999999999999999999LL})
		assert(linearRec({0, 1}, {1, 1}, k) == fib(k));
	cout << "Tests passed!" << endl;
}
