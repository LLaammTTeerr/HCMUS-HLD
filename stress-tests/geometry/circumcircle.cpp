#include "../utilities/template.h"

#include "../../content/geometry/circumcircle.h"

int main() {
	mt19937 rng(4);
	auto rd = [&]() { return (double)(rng() % 2001) / 100 - 10; };
	int done = 0;
	while (done < 100000) {
		P a(rd(), rd()), b(rd(), rd()), c(rd(), rd());
		if (abs((b - a).cross(c - a)) < 1) continue; // avoid near-degenerate
		done++;
		P o = ccCenter(a, b, c);
		double r = ccRadius(a, b, c);
		double da = (a - o).dist(), db = (b - o).dist(), dc = (c - o).dist();
		double tol = 1e-7 * max(1.0, r);
		assert(abs(da - r) < tol && abs(db - r) < tol && abs(dc - r) < tol);
	}
	cout << "Tests passed!" << endl;
}
