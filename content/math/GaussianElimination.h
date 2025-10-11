/**
 * Author: Phan Binh Nguyen Lam
 * Date: 2024-11-07
 * License: CC0
 * Description: Gaussian Elimination for solving systems of linear equations.
 * Usage:
 *  gauss({{1, 2, 3}, {4, 5, 6}}); // returns {1, -2}
 *  can be use for modulo arithmetic, but be careful with division
 *  replace Z with the desired type
 * Time: $O(N^3)$
 */
#pragma once

using Z = double;

std::vector <Z>* gauss(std::vector <std::vector <Z>> a) {
  #define ABS(x) ((x) < 0 ? -(x) : (x))
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;

	std::vector <int> pivot(m, -1);

	for (int col = 0, row = 0; col < m and row < n; col++) {
		int cur = row;
		for (int i = row; i < n; i++)
			if (ABS(a[i][col]) > ABS(a[cur][col]))
				cur = i;
		if (a[cur][col] == 0)
			continue;
		for (int i = col; i <= m; i++)
			swap(a[cur][i], a[row][i]);
		pivot[col] = row;

		for (int i = 0; i < n; i++) if (i != row) {
			if (a[i][col] == 0)
				continue;
			Z c = a[i][col] / a[row][col];
			for (int j = col; j <= m; j++)
				a[i][j] -= a[row][j] * c;
		}
		row++;
	}

	std::vector <Z> *ans = new std::vector <Z> (m, 0);
	for (int i = 0; i < m; i++) if (pivot[i] != -1)
		(*ans)[i] = a[pivot[i]][m] / a[pivot[i]][i];
	for (int i = 0; i < n; i++) {
		Z s = a[i][m];
		for (int j = 0; j < m; j++)
			s -= (*ans)[j] * a[i][j];
		if (s)
			return nullptr;
	}

	return ans;
  #undef ABS
}