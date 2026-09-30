/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Description: Modular exponentiation; mod must be prime for inverses.
 * Time: O(\log e)
 */
#pragma once

const ll mod = 1000000007; // faster if const

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (b %= mod; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
