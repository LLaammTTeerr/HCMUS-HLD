#include "../utilities/template.h"
// Non-commutative op: compose affine maps x -> a*x + b (mod P).
// The header uses `ll` as its value type and `+` as f, so we
// include it in a namespace where ll is an affine-map type whose
// default value is the identity.
const ll P = 1e9 + 7;
struct Aff {
	ll a, b;
	constexpr Aff(int = 0) : a(1), b(0) {}
	constexpr Aff(ll a, ll b) : a(a), b(b) {}
	Aff operator+(const Aff& o) const { // apply this, then o
		return {a * o.a % P, (b * o.a + o.b) % P};
	}
	bool operator==(const Aff& o) const { return a == o.a && b == o.b; }
};
namespace NC {
	typedef Aff ll;
#include "../../content/data-structure/ZKWSegTree.h"
}

int main() {
	mt19937 rng(2);
	rep(it,0,3000) {
		int n = 1 + rng() % 40;
		vector<Aff> a(n);
		for (auto& x : a) x = Aff(rng() % P, rng() % P);
		NC::ZKW st(a);
		rep(q,0,100) {
			if (rng() % 2) {
				int p = rng() % n;
				a[p] = Aff(rng() % P, rng() % P); st.update(p, a[p]);
			} else {
				int l = rng() % (n + 1), r = rng() % (n + 1);
				if (l > r) swap(l, r);
				Aff s;
				rep(i,l,r) s = s + a[i];
				assert(st.query(l, r) == s);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
