#include "../utilities/template.h"

#include "../../content/geometry/kdTree.h"

int main() {
	mt19937 rng(5);
	rep(it,0,300) {
		int n = 1 + (int)(rng() % 300), C = it % 2 ? 20 : 1000000000;
		auto rc = [&]() { return (T)(rng() % (2 * C + 1)) - C; };
		vector<P> ps(n);
		for (auto& p : ps) p = P(rc(), rc());
		KDTree kd(ps);
		rep(q,0,200) {
			P p(rc(), rc());
			if (q % 4 == 0) p = ps[rng() % n]; // query an existing point
			T best = INF;
			for (auto& x : ps) best = min(best, (x - p).dist2());
			auto [d, pt] = kd.nearest(p);
			assert(d == best && (pt - p).dist2() == best);
			assert(find(all(ps), pt) != ps.end());
		}
	}
	cout << "Tests passed!" << endl;
}
