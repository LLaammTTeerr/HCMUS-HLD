#include "../utilities/template.h"
#include "../../content/math/InverseModulo.h"

int main() {
	mt19937 rng(1);
	rep(m,2,300) rep(a,-300,300) {
		if (__gcd(abs(a), m) != 1) continue;
		ll x = inverse_modulo<ll>(a, m);
		assert(0 <= x && x < m);
		assert(((a % m + m) % m) * x % m == 1 % m);
	}
	rep(it,0,100000) {
		ll m = (ll)(rng() % 1000000000) + 2, a = (ll)(rng() % 2000000001) - 1000000000;
		if (__gcd(abs(a), m) != 1) continue;
		ll x = inverse_modulo<ll>(a, m);
		assert(0 <= x && x < m);
		assert((__int128)((a % m + m) % m) * x % m == 1);
	}
	cout << "Tests passed!" << endl;
}
