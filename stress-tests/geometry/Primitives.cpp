#include "../utilities/template.h"

// Point.h, sideOf.h, OnSegment.h, lineDistance.h
#include "../../content/geometry/Point.h"
#include "../../content/geometry/sideOf.h"
#include "../../content/geometry/OnSegment.h"
#include "../../content/geometry/lineDistance.h"

typedef Point<ll> PL;
typedef Point<double> PD;

int main() {
	mt19937 rng(1);
	auto ri = [&](int lo, int hi) { return lo + (int)(rng() % (hi - lo + 1)); };
	rep(it,0,200000) {
		PL a(ri(-6, 6), ri(-6, 6)), b(ri(-6, 6), ri(-6, 6)), p(ri(-6, 6), ri(-6, 6));
		// Point basics
		assert((a + b) - b == a && a * 3 == a + a + a);
		assert(a.dot(b) == a.x * b.x + a.y * b.y);
		assert(a.cross(b) == a.x * b.y - a.y * b.x);
		assert(p.cross(a, b) == (a - p).cross(b - p));
		assert(a.dist2() == a.x * a.x + a.y * a.y);
		assert(a.perp() == PL(-a.y, a.x));
		// sideOf: sign of orientation
		ll cr = (b - a).x * (p - a).y - (b - a).y * (p - a).x;
		assert(sideOf(a, b, p) == (cr > 0) - (cr < 0));
		// onSegment: collinear and inside bounding box
		bool on = cr == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
			min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
		assert(onSegment(a, b, p) == on);
		if (a == b) continue;
		// lineDist: signed distance, positive on the left of a->b
		PD da((double)a.x, (double)a.y), db((double)b.x, (double)b.y),
			dp((double)p.x, (double)p.y);
		double want = (double)cr / sqrt((double)(b - a).dist2());
		assert(abs(lineDist(da, db, dp) - want) < 1e-9);
		// sideOf with eps agrees away from the line
		if (abs(want) > 1e-6) assert(sideOf(da, db, dp, 1e-9) == sideOf(a, b, p));
	}
	rep(it,0,100000) {
		PD p(rng() % 2001 / 100.0 - 10, rng() % 2001 / 100.0 - 10);
		double t = rng() % 6283 / 1000.0;
		PD q = p.rotate(t);
		assert(abs(q.dist() - p.dist()) < 1e-9);
		if (p.dist() > 1e-9) {
			assert(abs(p.unit().dist() - 1) < 1e-9);
			double d = q.angle() - p.angle() - t;
			d = remainder(d, 2 * M_PI);
			assert(abs(d) < 1e-9);
			assert(abs(p.normal().dot(p)) < 1e-9);
		}
	}
	cout << "Tests passed!" << endl;
}
