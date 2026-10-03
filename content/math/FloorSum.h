/**
 * Author: HCMUS-HLD
 * Description: $\sum_{i=0}^{n-1} \lfloor \frac{ai + b}{m} \rfloor$ for
 * $n \ge 0$, $m > 0$, any sign of a, b. Needs $n, m \le 2 \cdot 10^9$
 * and the answer to fit in ll. Sum over $i \in [l, r]$:
 * floorSum(r - l + 1, m, a, a * l + b).
 * Time: O(\log m)
 */
#pragma once

ll floorSum(ll n, ll m, ll a, ll b) {
	ll ans = 0;
	if (a < 0) { // shift a, b into [0, m)
		ll q = (a % m + m - a) / m;
		ans -= n * (n - 1) / 2 * q, a += q * m;
	}
	if (b < 0) {
		ll q = (b % m + m - b) / m;
		ans -= n * q, b += q * m;
	}
	while (true) { // a, b >= 0
		ans += n * (n - 1) / 2 * (a / m) + n * (b / m);
		a %= m, b %= m;
		ll y = a * n + b;
		if (y < m) return ans;
		n = y / m, b = y % m, swap(m, a);
	}
}
