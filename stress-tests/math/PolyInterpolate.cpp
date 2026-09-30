#include "../utilities/template.h"
#include "../../content/math/PolyInterpolate.h"

int main() {
	mt19937 rng(2);
	rep(it,0,2000) {
		int n = 1 + rng() % 8;
		vd a(n), x(n), y(n);
		for (auto& c : a) c = (int)(rng() % 21) - 10;
		set<int> used;
		rep(i,0,n) {
			int v;
			do v = (int)(rng() % 21) - 10; while (used.count(v));
			used.insert(v); x[i] = v;
			double p = 1; y[i] = 0;
			rep(j,0,n) y[i] += a[j] * p, p *= x[i];
		}
		vd r = interpolate(x, y, n);
		rep(j,0,n) assert(fabs(r[j] - a[j]) < 1e-6);
	}
	cout << "Tests passed!" << endl;
}
