/**
 * Author: HCMUS-HLD
 * Description: Minkowski sum $\{a + b\}$ of two convex polygons
 * given ccw without collinear points (as convexHull returns).
 * Result is ccw, without collinear points, starting at the
 * lowest (then leftmost) point. Distance between convex A and B
 * = distance from the origin to A + (-B).
 * Time: O(N + M)
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;
vector<P> minkowski(vector<P> a, vector<P> b) {
	for (auto* p : {&a, &b}) {
		rotate(p->begin(), min_element(all(*p), [](P x, P y) {
			return tie(x.y, x.x) < tie(y.y, y.x); }), p->end());
		p->push_back((*p)[0]), p->push_back((*p)[1]);
	}
	vector<P> r;
	int i = 0, j = 0, n = sz(a) - 2, m = sz(b) - 2;
	while (i < n || j < m) {
		r.push_back(a[i] + b[j]);
		ll c = (a[i + 1] - a[i]).cross(b[j + 1] - b[j]);
		if (c >= 0 && i < n) i++;
		if (c <= 0 && j < m) j++;
	}
	return r;
}
