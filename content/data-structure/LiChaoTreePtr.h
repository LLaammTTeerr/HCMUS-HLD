/**
 * Author: HCMUS-HLD
 * Description: Li Chao tree for MAXIMUM, dynamic nodes.
 * update(L, R, u, v, line) adds line on x in [u, v] (use
 * u=L, v=R for a full line); query(L, R, x). L, R = domain.
 * For minimum insert (-a, -b) and negate the answer.
 * Answers below -INF are clamped to -INF.
 * Time: O(\log C) per full line, O(\log^2 C) per segment.
 */
#pragma once

const ll INF = (ll)1e18;

struct LiLine {
	ll a, b;

	LiLine(ll a = 0, ll b = -INF) : a(a), b(b) {}

	inline ll operator () (ll x) const { return a * x + b; }
};

struct LiChao {
	LiLine value;
	LiChao* lef;
	LiChao* rig;

	LiChao(void) : value(LiLine()), lef(nullptr), rig(nullptr) {}

	void update(int l, int r, int u, int v, const LiLine& LINE) {
		if (l > r or u > v or u > r or l > v)
			return;

		if (u <= l and r <= v) {
			LiLine current = value, other = LINE;
			if (current(l) > other(l))
				swap(current, other);

			if (current(r) <= other(r))
				value = other;
			else {
				if (l == r)
					return;
				int m = (l + r) >> 1;
				if (current(m) > other(m)) {
					value = current;
					lef = lef ? lef : new LiChao();
					lef->update(l, m, u, v, other);
				} else {
					value = other;
					rig = rig ? rig : new LiChao();
					rig->update(m + 1, r, u, v, current);
				}
			}
			return;
		}

		int m = (l + r) >> 1;
		lef = lef ? lef : new LiChao();
		rig = rig ? rig : new LiChao();

		lef->update(l, m, u, v, LINE);
		rig->update(m + 1, r, u, v, LINE);
	}

	ll query(int l, int r, int x) {
		if (l > r or x > r or l > x)
			return -INF;
		ll ans = value(x);

		int m = (l + r) >> 1;
		ans = max(ans, lef ? lef->query(l, m, x) : -INF);
		ans = max(ans, rig ? rig->query(m + 1, r, x) : -INF);
		return ans;
	}
};