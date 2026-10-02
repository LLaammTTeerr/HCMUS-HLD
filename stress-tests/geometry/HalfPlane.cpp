#include "../utilities/template.h"
#include "../../content/geometry/HalfPlane.h"
#include "../../content/geometry/PolygonCut.h"
#include "../../content/geometry/PolygonArea.h"

int main() {
	mt19937 rng(31);
	auto R = [&](int c) { return (double)(int(rng() % (2 * c + 1)) - c); };
	int nonempty = 0;
	rep(it, 0, 100000) {
		const double B = 1000;
		vector<Line> v = {{P(-B, -B), P(B, -B)}, {P(B, -B), P(B, B)},
			{P(B, B), P(-B, B)}, {P(-B, B), P(-B, -B)}};
		int n = int(rng() % 8), c = it % 2 ? 3 : 20;
		rep(i, 0, n) {
			P s(R(c), R(c)), e(R(c), R(c));
			if (s == e) continue;
			v.push_back({s, e});
			if (rng() % 4 == 0) v.push_back({s, e}); // duplicate
			if (rng() % 6 == 0) v.push_back({e, s}); // opposite
		}
		shuffle(all(v), rng);
		vector<P> poly = {P(-B, -B), P(B, -B), P(B, B), P(-B, B)};
		for (auto& l : v) poly = polygonCut(poly, l[1], l[0]); // keep left
		double want = sz(poly) ? polygonArea2(poly) / 2 : 0;
		vector<P> r = halfPlanes(v);
		double got = sz(r) ? polygonArea2(r) / 2 : 0;
		assert(fabs(got - want) < 1e-6);
		if (sz(r)) {
			nonempty++;
			rep(i, 0, sz(r)) for (auto& l : v) // vertices satisfy all
				assert(l[0].cross(l[1], r[i]) > -1e-6);
			rep(i, 0, sz(r)) // ccw convex
				assert(r[i].cross(r[(i + 1) % sz(r)], r[(i + 2) % sz(r)]) > -1e-6);
		}
	}
	assert(nonempty > 30000);
	cout << "Tests passed!" << endl;
}
