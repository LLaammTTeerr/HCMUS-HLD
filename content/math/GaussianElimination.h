/**
 * Author: Phan Binh Nguyen Lam
 * Date: 2024-11-07
 * License: CC0
 * Description: Solves $Ax = b$ over doubles. Input is the augmented
 * $n \times (m+1)$ matrix $[A | b]$. Returns false if inconsistent;
 * otherwise x is one solution (free variables set to 0).
 * Usage: vector<double> x;
 * gauss({{1, 2, 3}, {4, 5, 6}}, x); // x = {-1, 2}
 * Time: O(N M \min(N, M))
 */
#pragma once

const double EPS = 1e-9;
bool gauss(vector<vector<double>> a, vector<double>& x) {
	int n = sz(a), m = n ? sz(a[0]) - 1 : 0;
	vi pivot(m, -1);
	for (int col = 0, row = 0; col < m && row < n; col++) {
		int cur = row;
		rep(i,row,n) if (fabs(a[i][col]) > fabs(a[cur][col])) cur = i;
		if (fabs(a[cur][col]) < EPS) continue;
		swap(a[cur], a[row]);
		pivot[col] = row;
		rep(i,0,n) if (i != row && fabs(a[i][col]) > EPS) {
			double c = a[i][col] / a[row][col];
			rep(j,col,m+1) a[i][j] -= a[row][j] * c;
		}
		row++;
	}
	x.assign(m, 0);
	rep(i,0,m) if (pivot[i] != -1)
		x[i] = a[pivot[i]][m] / a[pivot[i]][i];
	rep(i,0,n) {
		double s = a[i][m];
		rep(j,0,m) s -= x[j] * a[i][j];
		if (fabs(s) > EPS) return false;
	}
	return true;
}
