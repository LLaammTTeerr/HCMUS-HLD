/**
 * Author: HCMUS-HLD
 * Description: Aliens / Lagrangian relaxation. Maximize f(k)
 * where f(k) = best value using exactly k items and f is
 * concave. calc(lam) must solve the problem where each item
 * costs an extra lam, returning {best value, max count among
 * optimal solutions}. For minimization negate values.
 * Usage: aliens(k, [&](ll lam) { ...; return pair{v, c}; })
 * Time: O(\log C) calls to calc.
 */
#pragma once

template<class F> ll aliens(ll k, F calc) {
	ll lo = -1e12, hi = 1e12, ans = 0; // |lam| > max slope
	while (lo <= hi) {
		ll mid = lo + (hi - lo) / 2;
		auto [v, c] = calc(mid);
		if (c >= k) ans = v + mid * k, lo = mid + 1;
		else hi = mid - 1;
	}
	return ans;
}
