#include "../utilities/template.h"
#include "../../content/string/Hash.h"
// Dynamic strings: ZKW over HV (concatenation). The header's value
// type is `ll` with `static constexpr T unit = 0`; HV is not a
// literal type, so wrap it (HW(0) = empty string) and relax the
// constexpr for this include only.
struct HW : HV {
	HW(int = 0) : HV() {}
	HW(const HV& h) : HV(h) {}
};
namespace DYN {
	typedef HW ll;
#define constexpr inline const
#include "../../content/data-structure/ZKWSegTree.h"
#undef constexpr
}

int main() {
	initHash();
	mt19937 rng(18);
	// static: equality across strings, concatenation, bytes >= 128
	rep(it,0,1000) {
		string s, t;
		int n = 1 + rng() % 30, m = 1 + rng() % 30;
		rep(i,0,n) s += char(rng() % 2 ? 'a' : rng() % 2 ? 'b' : 200);
		rep(i,0,m) t += char(rng() % 2 ? 'a' : 'b');
		H a(s), b(t);
		rep(i,0,n) assert(a.get(i, i + 1) == HV((unsigned char)s[i]));
		rep(q,0,50) {
			int l1 = rng() % (n + 1), r1 = rng() % (n + 1);
			int l2 = rng() % (m + 1), r2 = rng() % (m + 1);
			if (l1 > r1) swap(l1, r1);
			if (l2 > r2) swap(l2, r2);
			string x = s.substr(l1, r1 - l1), y = t.substr(l2, r2 - l2);
			assert((a.get(l1, r1) == b.get(l2, r2)) == (x == y));
			string xy = x + y; H c(xy);
			assert(a.get(l1, r1) + b.get(l2, r2) == c.get(0, sz(xy)));
		}
	}
	// dynamic: point updates + substring comparison
	rep(it,0,500) {
		int n = 1 + rng() % 40;
		string s(n, 'a');
		for (char& ch : s) ch = char('a' + rng() % 3);
		vector<HW> leaves;
		for (char ch : s) leaves.push_back(HV((unsigned char)ch));
		DYN::ZKW st(leaves);
		rep(q,0,100) {
			if (rng() % 3 == 0) {
				int p = rng() % n;
				s[p] = char('a' + rng() % 3);
				st.update(p, HV((unsigned char)s[p]));
			} else {
				int l = rng() % (n + 1), r = rng() % (n + 1);
				if (l > r) swap(l, r);
				int len = r - l, l2 = rng() % (n - len + 1);
				bool eq = s.substr(l, len) == s.substr(l2, len);
				assert((st.query(l, r) == st.query(l2, l2 + len)) == eq);
				H h(s);
				assert(st.query(l, r) == h.get(l, r));
			}
		}
	}
	cout << "Tests passed!" << endl;
}
