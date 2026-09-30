#include "../utilities/template.h"

#include "../../content/geometry/SegmentDistance.h"

int main() {
	mt19937 rng(2);
	auto rd = [&]() { return (double)(rng() % 2001) / 100 - 10; };
	rep(it,0,20000) {
		P s(rd(), rd()), e(rd(), rd()), p(rd(), rd());
		if (it % 10 == 0) e = s; // degenerate segment
		double got = segDist(s, e, p);
		// brute: dense sampling + both endpoints
		double best = min((p - s).dist(), (p - e).dist());
		const int K = 2000;
		rep(k,0,K + 1) best = min(best, (p - (s + (e - s) * (k / (double)K))).dist());
		double step = (e - s).dist() / K;
		assert(got <= best + 1e-9);
		assert(got >= best - step - 1e-9);
		assert(got >= 0);
	}
	cout << "Tests passed!" << endl;
}
