#include "../utilities/template.h"

#include "../../content/geometry/linearTransformation.h"

int main() {
	mt19937 rng(3);
	auto rd = [&]() { return (double)(rng() % 2001) / 100 - 10; };
	rep(it,0,100000) {
		// random similarity: rotate by t, scale by k, translate by d
		double t = rd(), k = 0.1 + (rng() % 1000) / 100.0;
		P d(rd(), rd());
		auto T = [&](P x) { return x.rotate(t) * k + d; };
		P p0(rd(), rd()), p1(rd(), rd()), r(rd(), rd());
		if ((p1 - p0).dist() < 1e-3) continue;
		P got = linearTransformation(p0, p1, T(p0), T(p1), r);
		assert((got - T(r)).dist() < 1e-6 * max(1.0, T(r).dist()));
	}
	cout << "Tests passed!" << endl;
}
