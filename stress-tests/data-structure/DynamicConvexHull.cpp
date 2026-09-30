#include "../utilities/template.h"
#include "../../content/data-structure/DynamicConvexHull.h"

int main() {
	mt19937 rng(4);
	rep(it,0,1000) {
		DynamicHull h;
		vector<pair<ll, ll>> ls;
		int K = it % 3 == 0 ? 5 : 1000000000; // small => equal slopes
		rep(q,0,100) {
			if (ls.empty() || rng() % 2) {
				ll k = (ll)(rng() % (2 * K + 1)) - K;
				ll m = (ll)(rng() % 2000000001) - 1000000000;
				m *= 100000000; // |m| up to 1e17
				h.add(k, m), ls.push_back({k, m});
			} else {
				ll x = (ll)(rng() % 2000000001) - 1000000000;
				ll best = LLONG_MIN;
				for (auto [k, m] : ls) best = max(best, k * x + m);
				assert(h.query(x) == best);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
