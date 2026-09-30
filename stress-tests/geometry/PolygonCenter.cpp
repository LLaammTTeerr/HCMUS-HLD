#include "../utilities/template.h"

#include "../../content/geometry/PolygonCenter.h"
#include "../../content/geometry/PolygonArea.h"
#include "genPolygon.h"

int main() {
	srand(8);
	rep(it,0,20000) {
		vector<Point<double>> pts(3 + rand() % 10);
		for (auto& p : pts) p = Point<double>(rand() % 20, rand() % 20);
		auto poly = genPolygon(pts); // simple polygon, ccw
		int n = sz(poly);
		if (n < 3) continue;
		double A2 = polygonArea2(poly);
		if (abs(A2) < 1e-9) continue;
		// brute: fan triangulation, area-weighted triangle centroids
		Point<double> s(0, 0);
		double tw = 0;
		rep(i,1,n - 1) {
			double w = (poly[i] - poly[0]).cross(poly[i + 1] - poly[0]);
			s = s + (poly[0] + poly[i] + poly[i + 1]) / 3 * w;
			tw += w;
		}
		auto c = polygonCenter(poly), want = s / tw;
		assert((c - want).dist() < 1e-6);
	}
	cout << "Tests passed!" << endl;
}
