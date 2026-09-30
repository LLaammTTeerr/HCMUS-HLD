/**
 * Author: HCMUS-HLD
 * Description: Non-negative big integer, base $10^9$ limbs
 * (little-endian, no leading zero limbs; 0 is empty). Sections
 * are independent, delete what the problem doesn't need; only
 * big / big needs [+-] and [small]. For signs keep a bool beside.
 * Usage: Big a("123456789012345678901"), b(42);
 * cout << (a * b + 7).str(); auto [q, r] = a.divmod(b);
 * Time: +, -, small ops $O(n)$; $\times$ $O(nm)$; big div
 * $O(nm \log B)$ with $n, m$ = number of limbs. In practice:
 * $\times$ of two $10^5$-digit numbers 0.2 s; big / fine up to
 * $\approx 3 \cdot 10^4$ digits (0.75 s).
 */
#pragma once

const ll B = 1e9;
struct Big {
	vector<ll> d;
	// [core]
	Big(ll x = 0) { for (; x; x /= B) d.push_back(x % B); }
	Big(const string& s) {
		for (int i = sz(s); i > 0; i -= 9) {
			int j = max(0, i - 9);
			d.push_back(stoll(s.substr(j, i - j)));
		}
		trim();
	}
	void trim() { while (sz(d) && !d.back()) d.pop_back(); }
	string str() const {
		if (d.empty()) return "0";
		string s = to_string(d.back());
		for (int i = sz(d) - 1; i--;) {
			string t = to_string(d[i]);
			s += string(9 - sz(t), '0') + t;
		}
		return s;
	}
	bool operator<(const Big& o) const {
		if (sz(d) != sz(o.d)) return sz(d) < sz(o.d);
		return lexicographical_compare(d.rbegin(), d.rend(),
			o.d.rbegin(), o.d.rend());
	}
	bool operator==(const Big& o) const { return d == o.d; }
	// [+-] a - b needs a >= b
	Big operator+(const Big& o) const {
		Big r; ll c = 0;
		for (int i = 0; i < max(sz(d), sz(o.d)) || c; i++) {
			c += (i < sz(d) ? d[i] : 0) + (i < sz(o.d) ? o.d[i] : 0);
			r.d.push_back(c % B), c /= B;
		}
		return r;
	}
	Big operator-(const Big& o) const {
		Big r = *this; ll c = 0;
		for (int i = 0; i < sz(o.d) || c; i++) {
			r.d[i] -= c + (i < sz(o.d) ? o.d[i] : 0);
			if ((c = r.d[i] < 0)) r.d[i] += B;
		}
		r.trim(); return r;
	}
	// [small] 0 <= m < 9e9
	Big operator*(ll m) const {
		Big r; ll c = 0;
		for (int i = 0; i < sz(d) || c; i++) {
			c += i < sz(d) ? d[i] * m : 0;
			r.d.push_back(c % B), c /= B;
		}
		r.trim(); return r;
	}
	pair<Big, ll> divmod(ll m) const {
		Big q = *this; ll r = 0;
		for (int i = sz(d); i--;)
			r = r * B + d[i], q.d[i] = r / m, r %= m;
		q.trim(); return {q, r};
	}
	// [big *]
	Big operator*(const Big& o) const {
		Big r; r.d.assign(sz(d) + sz(o.d) + 1, 0);
		rep(i,0,sz(d)) {
			ll c = 0;
			for (int j = 0; j < sz(o.d) || c; j++) {
				c += r.d[i+j] + (j < sz(o.d) ? d[i] * o.d[j] : 0);
				r.d[i+j] = c % B, c /= B;
			}
		}
		r.trim(); return r;
	}
	// [big /] needs [+-] and [small]; o > 0
	pair<Big, Big> divmod(const Big& o) const {
		Big q, r; q.d.resize(sz(d));
		for (int i = sz(d); i--;) {
			r.d.insert(r.d.begin(), d[i]), r.trim();
			ll lo = 0, hi = B - 1; // largest q.d[i]: o*q.d[i] <= r
			while (lo < hi) {
				ll m = (lo + hi + 1) / 2;
				if (r < o * m) hi = m - 1; else lo = m;
			}
			q.d[i] = lo, r = r - o * lo;
		}
		q.trim(); return {q, r};
	}
};
