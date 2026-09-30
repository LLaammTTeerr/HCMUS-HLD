#include "../utilities/template.h"

// 3dHull.h, Point3D.h, PolyhedronVolume.h
#include "../../content/geometry/Point3D.h"
#include "../../content/geometry/3dHull.h"
#include "../../content/geometry/PolyhedronVolume.h"

int main() {
	mt19937 rng(9);
	auto ru = [&]() { return (rng() % 1000001) / 1e6; };
	// Point3D basics
	rep(it,0,100000) {
		P3 a(ru() - .5, ru() - .5, ru() - .5), b(ru() - .5, ru() - .5, ru() - .5);
		P3 c = a.cross(b);
		assert(abs(c.dot(a)) < 1e-12 && abs(c.dot(b)) < 1e-12);
		double ang = ru() * 6;
		P3 r = a.rotate(ang, b);
		assert(abs(r.dist() - a.dist()) < 1e-9);          // length kept
		assert(abs(r.dot(b.unit()) - a.dot(b.unit())) < 1e-9); // axis part kept
		assert(abs(a.phi() - atan2(a.y, a.x)) < 1e-12);
		assert(abs(a.theta() - acos(a.z / a.dist())) < 1e-6);
	}
	// hull of random points in a tetrahedron of known volume
	rep(it,0,300) {
		int n = 4 + (int)(rng() % 60);
		vector<P3> A = {P3(0, 0, 0), P3(3, 0, 0), P3(0, 3, 0), P3(0, 0, 3)};
		while (sz(A) < n) {
			P3 p(ru() * 3, ru() * 3, ru() * 3);
			if (p.x + p.y + p.z < 3 - 1e-3) A.push_back(p);
		}
		shuffle(all(A), rng);
		auto FS = hull3d(A);
		assert(sz(FS) == 4); // the tetrahedron's faces
		assert(abs(signedPolyVolume(A, FS) - 4.5) < 1e-9);
	}
	// random points: every point is inside every face; Euler; volume
	rep(it,0,300) {
		int n = 4 + (int)(rng() % 80);
		vector<P3> A(n);
		for (auto& p : A) p = P3(ru(), ru(), ru());
		auto FS = hull3d(A);
		set<int> vs;
		for (auto& f : FS) {
			vs.insert(f.a), vs.insert(f.b), vs.insert(f.c);
			for (auto& p : A) assert(f.q.dot(p - A[f.a]) <= 1e-9);
		}
		assert(sz(FS) == 2 * sz(vs) - 4);
		double V = signedPolyVolume(A, FS);
		// brute volume: tetrahedra from an interior point to each face
		P3 o;
		for (int v : vs) o = o + A[v];
		o = o / (double)sz(vs);
		double W = 0;
		for (auto& f : FS)
			W += abs((A[f.a] - o).cross(A[f.b] - o).dot(A[f.c] - o)) / 6;
		assert(V > 0 && abs(V - W) < 1e-9);
	}
	cout << "Tests passed!" << endl;
}
