#include "../utilities/template.h"

#include "../../content/geometry/sphericalDistance.h"

int main() {
	mt19937 rng(6);
	auto ru = [&]() { return (rng() % 1000001) / 1e6; };
	rep(it,0,200000) {
		// f = longitude in [-pi, pi], t = angle from the z-axis in [0, pi]
		double f1 = (2 * ru() - 1) * M_PI, t1 = ru() * M_PI;
		double f2 = (2 * ru() - 1) * M_PI, t2 = ru() * M_PI;
		double r = 0.5 + ru() * 10;
		double got = sphericalDistance(f1, t1, f2, t2, r);
		// brute: angle between the unit vectors
		double ux = sin(t1) * cos(f1), uy = sin(t1) * sin(f1), uz = cos(t1);
		double vx = sin(t2) * cos(f2), vy = sin(t2) * sin(f2), vz = cos(t2);
		double cx = uy * vz - uz * vy, cy = uz * vx - ux * vz, cz = ux * vy - uy * vx;
		double ang = atan2(sqrt(cx * cx + cy * cy + cz * cz), ux * vx + uy * vy + uz * vz);
		assert(abs(got - r * ang) < 1e-6 * r);
	}
	cout << "Tests passed!" << endl;
}
