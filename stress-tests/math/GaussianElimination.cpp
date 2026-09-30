#include "../utilities/template.h"
#include "../../content/math/GaussianElimination.h"

int main() {
	mt19937 rng(5);
	vector<double> x;
	assert(gauss({}, x) && x.empty());
	assert(gauss({{1, 2, 3}, {4, 5, 6}}, x));
	assert(fabs(x[0] + 1) < 1e-9 && fabs(x[1] - 2) < 1e-9);
	assert(gauss({{0.1, 0.1, 1}, {0.2, 0.6, 1}}, x));
	assert(!gauss({{1, 1, 1}, {1, 1, 2}}, x)); // inconsistent
	rep(it,0,3000) {
		int n = 1 + rng() % 6, m = 1 + rng() % 6;
		// consistent system from a known solution, possibly rank deficient
		vector<double> sol(m);
		for (auto& v : sol) v = (int)(rng() % 21) - 10;
		vector<vector<double>> a(n, vector<double>(m + 1));
		rep(i,0,n) {
			if (i && rng() % 4 == 0) a[i] = a[rng() % i]; // duplicate row
			else rep(j,0,m) a[i][j] = (int)(rng() % 11) - 5;
			a[i][m] = 0;
			rep(j,0,m) a[i][m] += a[i][j] * sol[j];
		}
		bool broken = n > 1 && rng() % 5 == 0;
		if (broken) a[0][m] += 1; // may become inconsistent
		bool ok = gauss(a, x);
		if (!broken) assert(ok);
		if (ok) rep(i,0,n) {
			double s = 0;
			rep(j,0,m) s += a[i][j] * x[j];
			assert(fabs(s - a[i][m]) < 1e-6);
		}
	}
	cout << "Tests passed!" << endl;
}
