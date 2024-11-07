/**
 * Author: Phan Binh Nguyen Lam
 * Date: 2024-11-07
 * License: CC0
 * Description: LiChao Segment Tree for finding maximum value of ax + b on intervals.
 * Usage: Lichao<MAX> tree;
 */
#pragma once

const long long LINF = 1E18 + 7;

template <int MAX>
class LiChao {
private:
	struct Line {
		long long A, B;

		Line(long long A = 0, long long B = 0): A(A), B(B) { }
		inline long long operator () (long long X) const { return A * X + B; }
	} st[4 * MAX + 7];

	void add_line(int id, int l, int r, const Line &vars) {
		if (l > r) return;
		Line cur = st[id], L = vars;

		if (cur(l) < L(l)) swap(cur, L);
		if (cur(r) >= L(r)) st[id] = L;
		else {
			int mid = (l + r) >> 1;
			if (cur(mid) > L(mid)) st[id] = L, add_line(id << 1 | 1, mid + 1, r, cur);
			else st[id] = cur, add_line(id << 1, l, mid, L);
		}
	}

	long long query(int id, int l, int r, long long X) const {
		if (l > r || X < l || X > r) return LINF;

		long long res = st[id] (X);
		if (l == r) return res;

		int mid = (l + r) >> 1;
		res = min(res, query(id << 1, l, mid, X));
		res = min(res, query(id << 1 | 1, mid + 1, r, X));

		return res;
	}
public:
	LiChao(void) { }

	void add_line(long long A, long long B) { add_line(1, 0, MAX, Line(A, B)); }
	long long query(long long X) const { return query(1, 0, MAX, X); }
};