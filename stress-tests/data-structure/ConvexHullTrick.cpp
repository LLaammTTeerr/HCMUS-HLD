#include "../utilities/template.h"
#include "../../content/data-structure/ConvexHullTrick.h"

int main() {
	mt19937 rng(7);
	rep(it,0,2000) {
		int K = it % 3 == 0 ? 3 : 1000000000; // small => equal slopes
		int n = rng() % 60 + 1;
		vector<pair<ll, ll>> ls;
		rep(i,0,n) {
			ll k = (ll)(rng() % (2 * K + 1)) - K;
			ll m = (ll)(rng() % 2000000001) - 1000000000;
			if (it % 2) m *= 100000000; // |m| up to 1e17
			ls.push_back({k, m});
		}
		sort(all(ls));
		bool mn = it % 4 == 1; // minimum: add (-k, -m) in reverse
		if (mn) reverse(all(ls));
		MonoHull h;
		vector<pair<ll, ll>> added;
		for (auto [k, m] : ls) {
			if (mn) h.add(-k, -m); else h.add(k, m);
			added.push_back({k, m});
			rep(q,0,5) {
				ll x = (ll)(rng() % 2000000001) - 1000000000;
				if (q == 0) x = rng() % 2 ? 1000000000 : -1000000000;
				if (q == 1) x = (ll)(rng() % 21) - 10;
				ll best = mn ? LLONG_MAX : LLONG_MIN;
				for (auto [a, b] : added)
					best = mn ? min(best, a * x + b) : max(best, a * x + b);
				assert((mn ? -h.query(x) : h.query(x)) == best);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
