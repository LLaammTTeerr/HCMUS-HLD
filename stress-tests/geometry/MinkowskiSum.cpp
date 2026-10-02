#include "../utilities/template.h"
#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/MinkowskiSum.h"

int main() {
	mt19937 rng(32);
	rep(it, 0, 50000) {
		vector<P> pa, pb;
		int c = it % 2 ? 3 : 1000000;
		auto R = [&]() { return (ll)(rng() % (2 * c + 1)) - c; };
		int na = int(rng() % 8) + 1, nb = int(rng() % 8) + 1;
		rep(i, 0, na) pa.push_back(P(R(), R()));
		rep(i, 0, nb) pb.push_back(P(R(), R()));
		vector<P> a = convexHull(pa), b = convexHull(pb), all_;
		for (P x : a) for (P y : b) all_.push_back(x + y);
		vector<P> want = convexHull(all_);
		// rotate to the lowest-then-leftmost point
		rotate(want.begin(), min_element(all(want), [](P x, P y) {
			return tie(x.y, x.x) < tie(y.y, y.x); }), want.end());
		vector<P> got = minkowski(a, b);
		if (sz(a) >= 3 && sz(b) >= 3) assert(got == want);
		else { // degenerate inputs: same hull
			vector<P> g2 = convexHull(got);
			rotate(g2.begin(), min_element(all(g2), [](P x, P y) {
				return tie(x.y, x.x) < tie(y.y, y.x); }), g2.end());
			assert(g2 == want);
		}
	}
	cout << "Tests passed!" << endl;
}
