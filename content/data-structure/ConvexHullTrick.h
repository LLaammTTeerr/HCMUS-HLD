#pragma once

using i64 = int64_t;

const int inf = 1e9 + 7;

i64 ceil_div(i64 a, i64 b) {
	if (b < 0)
		return ceil_div(-a, -b);
	return a < 0 ? a / b : (a + b - 1) / b;
}

class ConvexHullMax {
private:
	struct Line {
		i64 x, a, b;

		Line(i64 _x = -inf, i64 _a = -inf, i64 _b = -inf) : x(_x), a(_a), b(_b) {}

		inline i64 operator () (i64 x) const {
			return a * x + b;
		}

		inline i64 operator ^ (const Line& other) const {
			return ceil_div(other.b - b, a - other.a);
		}

		inline bool operator < (const Line& other) const {
			return x < other.x;
		}
	};

	std::vector <Line> q;
public:
	void insert(i64 a, i64 b) {
		Line l(-inf, a, b);

		while (not q.empty() and (q.back() ^ l) < q.back().x)
			q.pop_back();

		l.x = q.empty() ? -inf : q.back() ^ l;
		q.push_back(l);
	}

	i64 query(i64 x) const {
		return (*std::prev(std::upper_bound(q.begin(), q.end(), Line(x)))) (x);
	}
};
