#include "../utilities/template.h"

#include "../../content/geometry/Angle.h"

// Total angle of a (direction in [0, 2pi) plus t full turns).
double tot(Angle a) {
	double th = atan2((double)a.y, (double)a.x);
	if (th < 0) th += 2 * M_PI;
	return th + 2 * M_PI * a.t;
}

int main() {
	mt19937 rng(7);
	auto ri = [&]() { return (int)(rng() % 41) - 20; };
	auto ra = [&]() {
		int x, y;
		do x = ri(), y = ri(); while (!x && !y);
		return Angle(x, y, (int)(rng() % 3) - 1);
	};
	rep(it,0,300000) {
		Angle a = ra(), b = ra();
		// operator< vs total angle; same direction and turn = equal
		bool same = a.t == b.t &&
			(ll)a.x * b.y == (ll)a.y * b.x && (ll)a.x * b.x + (ll)a.y * b.y > 0;
		if (same) assert(!(a < b) && !(b < a));
		else assert((a < b) == (tot(a) < tot(b)));
		// rotations
		assert(abs(tot(a.t90()) - tot(a) - M_PI / 2) < 1e-9);
		assert(abs(tot(a.t180()) - tot(a) - M_PI) < 1e-9);
		assert(abs(tot(a.t360()) - tot(a) - 2 * M_PI) < 1e-9);
		// angleDiff(a, b) = angle b - angle a
		Angle d = angleDiff(a, b);
		if (d.x || d.y) assert(abs(tot(d) - (tot(b) - tot(a))) < 1e-9);
		// segmentAngles: a turn of at most pi between them
		Angle p(a.x, a.y), q(b.x, b.y);
		auto [s, e] = segmentAngles(p, q);
		double w = tot(e) - tot(s);
		assert(-1e-9 <= w && w <= M_PI + 1e-9);
	}
	// sorting by angle matches atan2 order
	vector<Angle> v;
	rep(i,0,2000) { Angle a = ra(); a.t = 0; v.push_back(a); }
	sort(all(v));
	rep(i,1,sz(v)) assert(tot(v[i - 1]) <= tot(v[i]) + 1e-12);
	cout << "Tests passed!" << endl;
}
