#include "../utilities/template.h"

const ll P = 998244353;
struct Z {
	ll v;
	Z(ll x = 0) : v((x % P + P) % P) {}
	Z operator+(Z o) const { return Z(v + o.v); }
	Z operator-(Z o) const { return Z(v - o.v); }
	Z operator*(Z o) const { return Z(v * o.v); }
	Z pow(ll e) const { Z r = 1, b = *this; for (; e; e >>= 1, b = b * b) if (e & 1) r = r * b; return r; }
	Z operator/(Z o) const { return *this * o.pow(P - 2); }
	Z& operator+=(Z o) { return *this = *this + o; }
	bool operator==(Z o) const { return v == o.v; }
};

#include "../../content/math/BernoulliNumber.h"

int main() {
	// B^+ convention: 1, 1/2, 1/6, 0, -1/30, 0, 1/42, 0, -1/30
	vector<Z> B = bernoulli<Z>(60);
	vector<pair<ll,ll>> known = {{1,1},{1,2},{1,6},{0,1},{-1,30},{0,1},{1,42},{0,1},{-1,30},{0,1},{5,66}};
	rep(i,0,sz(known)) assert(B[i] == Z(known[i].first) / Z(known[i].second));
	assert(sz(bernoulli<Z>(0)) == 1);
	rep(k,0,61) rep(n,0,60) {
		Z s = 0;
		rep(i,1,n+1) s += Z(i).pow(k);
		assert(powerSum(n, k, B) == s);
	}
	// large n
	ll n = 1000000000000LL;
	assert(powerSum(n, 1, B) == Z(n) * Z(n + 1) / Z(2));
	assert(powerSum(n, 2, B) == Z(n) * Z(n + 1) * Z(2 * n + 1) / Z(6));
	cout << "Tests passed!" << endl;
}
