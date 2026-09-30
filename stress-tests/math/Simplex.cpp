#include "../utilities/template.h"
#include "../../content/math/Simplex.h"

// brute force: best vertex among all choices of n tight constraints
DOUBLE brute(VVD A, VD b, const VD& c, bool& feas) {
	int n = sz(c);
	rep(j,0,n) { VD r(n); r[j] = -1; A.push_back(r); b.push_back(0); }
	int M = sz(A);
	DOUBLE best = -1e18; feas = false;
	vi idx(n);
	function<void(int,int)> rec = [&](int s, int k) {
		if (k == n) {
			VVD G(n, VD(n + 1));
			rep(i,0,n) { rep(j,0,n) G[i][j] = A[idx[i]][j]; G[i][n] = b[idx[i]]; }
			rep(col,0,n) {
				int p = -1;
				rep(r,col,n) if (fabsl(G[r][col]) > 1e-9 && (p < 0 || fabsl(G[r][col]) > fabsl(G[p][col]))) p = r;
				if (p < 0) return;
				swap(G[p], G[col]);
				rep(r,0,n) if (r != col) {
					DOUBLE f = G[r][col] / G[col][col];
					rep(j,0,n+1) G[r][j] -= f * G[col][j];
				}
			}
			VD x(n);
			rep(i,0,n) x[i] = G[i][n] / G[i][i];
			rep(i,0,M) {
				DOUBLE s = 0;
				rep(j,0,n) s += A[i][j] * x[j];
				if (s > b[i] + 1e-7) return;
			}
			feas = true;
			DOUBLE v = 0;
			rep(j,0,n) v += c[j] * x[j];
			best = max(best, v);
			return;
		}
		rep(i,s,M) idx[k] = i, rec(i + 1, k + 1);
	};
	rec(0, 0);
	return best;
}

int main() {
	mt19937 rng(11);
	int feasible = 0, infeasible = 0;
	rep(it,0,3000) {
		int n = 1 + rng() % 3, m = 1 + rng() % 4;
		VVD A(m, VD(n)); VD b(m), c(n);
		rep(i,0,m) { rep(j,0,n) A[i][j] = (int)(rng() % 11) - 5; b[i] = (int)(rng() % 21) - 6; }
		rep(j,0,n) c[j] = (int)(rng() % 11) - 5;
		rep(j,0,n) { VD r(n); r[j] = 1; A.push_back(r); b.push_back(10); } // bounded
		bool feas;
		DOUBLE bv = brute(A, b, c, feas);
		LPSolver s(A, b, c);
		VD x;
		DOUBLE v = s.Solve(x);
		if (!feas) { infeasible++; assert(isinf(v) && v < 0); continue; }
		feasible++;
		assert(fabsl(v - bv) < 1e-6);
		rep(i,0,sz(b)) {
			DOUBLE t = 0;
			rep(j,0,n) t += A[i][j] * x[j];
			assert(t <= b[i] + 1e-7);
		}
		rep(j,0,n) assert(x[j] >= -1e-9);
	}
	assert(feasible > 1000 && infeasible > 100);
	VD x;
	LPSolver u({{1, -1}}, {1}, {1, 1}); // unbounded
	DOUBLE v = u.Solve(x);
	assert(isinf(v) && v > 0);
	LPSolver z(VVD{}, VD{}, VD{-1, -2}); // no constraints, optimum 0
	assert(fabsl(z.Solve(x)) < 1e-9);
	cout << "Tests passed!" << endl;
}
