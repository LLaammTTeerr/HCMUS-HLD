/**
 * Author: HCMUS-HLD
 * Description: Intersection of half-planes; line \{s, e\} keeps
 * the points on its left, $(e - s) \times (p - s) \ge 0$.
 * Returns the vertices in ccw order (a vertex may repeat if 3+
 * lines meet there), or empty if the area is 0.
 * The answer must be bounded: add a big bounding box if needed.
 * Time: O(N \log N)
 */
#pragma once

#include "Point.h"
#include "lineIntersection.h"

typedef Point<double> P;
typedef array<P, 2> Line;
vector<P> halfPlanes(vector<Line> v) {
	const double eps = 1e-9;
	auto d = [](const Line& l) { return l[1] - l[0]; };
	sort(all(v), [&](const Line& a, const Line& b) {
		return d(a).angle() < d(b).angle(); });
	auto out = [&](const Line& l, P p) {
		return l[0].cross(l[1], p) < -eps; };
	auto at = [](const Line& a, const Line& b) {
		return lineInter(a[0], a[1], b[0], b[1]).second; };
	deque<Line> q;
	for (auto& l : v) {
		while (sz(q) > 1 && out(l, at(q.end()[-1], q.end()[-2])))
			q.pop_back();
		while (sz(q) > 1 && out(l, at(q[0], q[1]))) q.pop_front();
		if (sz(q) && fabs(d(l).cross(d(q.back()))) < eps) {
			if (d(l).dot(d(q.back())) < 0) return {};
			if (!out(l, q.back()[0])) continue;
			q.pop_back();
		}
		q.push_back(l);
	}
	while (sz(q) > 2 && out(q[0], at(q.end()[-1], q.end()[-2])))
		q.pop_back();
	while (sz(q) > 2 && out(q.back(), at(q[0], q[1])))
		q.pop_front();
	if (sz(q) < 3) return {};
	vector<P> r;
	rep(i, 0, sz(q)) r.push_back(at(q[i], q[(i + 1) % sz(q)]));
	double A = 0;
	rep(i, 0, sz(r)) A += r[i].cross(r[(i + 1) % sz(r)]);
	return A > eps ? r : vector<P>();
}
