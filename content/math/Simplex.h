/**
 * Author: Stanford ACM notebook
 * Description: Two-phase simplex. Solves max $c^T x$ s.t. $Ax \le b$,
 * $x \ge 0$ ($A$ is $m \times n$). Solve(x) returns the optimum and
 * stores an optimal x; returns inf if unbounded, -inf if infeasible.
 * Usage: LPSolver lp(A, b, c); VD x; DOUBLE v = lp.Solve(x);
 * Time: O(NM) per pivot, exponential worst case
 */
#pragma once

typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

const DOUBLE EPS = 1e-9;

struct LPSolver {
	int m, n;
	VI B, N;
	VVD D;

	LPSolver(const VVD &A, const VD &b, const VD &c) :
		m(b.size()), n(c.size()), B(m), N(n + 1), D(m + 2, VD(n + 2)) {
			for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
			for (int i = 0; i < m; i++) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
			for (int j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
			N[n] = -1; D[m + 1][n] = 1;
		}

	void Pivot(int r, int s) {
		for (int i = 0; i < m + 2; i++) if (i != r)
			for (int j = 0; j < n + 2; j++) if (j != s)
				D[i][j] -= D[r][j] * D[i][s] / D[r][s];
		for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] /= D[r][s];
		for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] /= -D[r][s];
		D[r][s] = 1.0 / D[r][s];
		swap(B[r], N[s]);
	}

	bool Simplex(int phase) {
		int x = phase == 1 ? m + 1 : m;
		while (true) {
			int s = -1;
			for (int j = 0; j <= n; j++) {
				if (phase == 2 && N[j] == -1) continue;
				if (s == -1 || D[x][j] < D[x][s] || (D[x][j] == D[x][s] && N[j] < N[s])) s = j;
			}
			if (D[x][s] > -EPS) return true;
			int r = -1;
			for (int i = 0; i < m; i++) {
				if (D[i][s] < EPS) continue;
				if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] || ((D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r])) r = i;
			}
			if (r == -1) return false;
			Pivot(r, s);
		}
	}

	DOUBLE Solve(VD &x) {
		int r = 0;
		for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
		if (D[r][n + 1] < -EPS) {
			Pivot(r, n);
			if (!Simplex(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<DOUBLE>::infinity();
			for (int i = 0; i < m; i++) if (B[i] == -1) {
				int s = -1;
				for (int j = 0; j <= n; j++)
					if (s == -1 || D[i][j] < D[i][s] || (D[i][j] == D[i][s] && N[j] < N[s])) s = j;
				Pivot(i, s);
			}
		}
		if (!Simplex(2)) return numeric_limits<DOUBLE>::infinity();
		x = VD(n);
		for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
		return D[m][n + 1];
	}
};
