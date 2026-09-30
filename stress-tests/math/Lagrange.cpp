#include "../utilities/template.h"

typedef unsigned long long ull;
const ll P = 1000000007;
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

#include "../../content/math/Lagrange.h"

int main() {
	mt19937 rng(6);
	rep(it,0,2000) {
		int n = 1 + rng() % 10;
		vector<Z> c(n);
		for (auto& v : c) v = Z(rng());
		auto f = [&](ll x) { Z r = 0, p = 1; rep(j,0,n) r += c[j] * p, p = p * Z(x); return r; };
		vector<Z> p(n);
		rep(i,0,n) p[i] = f(i);
		vector<ll> xs = {0, (ll)n - 1, (ll)n, -1, -123456, P, P + 1, (ll)4e18,
			(ll)(rng() % 1000000) - 500000, (ll)((ull)rng() << 31 ^ rng())};
		for (ll x : xs) assert(lagrange(p, x) == f(x));
	}
	cout << "Tests passed!" << endl;
}
