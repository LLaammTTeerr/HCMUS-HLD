/**
 * Author: HCMUS-HLD
 * Description: $p(0..n)$ mod MOD, $p(i)$ = number of ways to write i as
 * a sum of positive integers, by Euler's pentagonal theorem.
 * Time: O(n \sqrt n)
 * Status: Library Checker partition\_function
 */
#pragma once

vector<ll> partitions(int n, ll MOD = 998244353) {
	vector<ll> dp(n + 1);
	dp[0] = 1;
	rep(i,1,n+1) for (int k = 1; ; ++k) {
		int g1 = k * (3 * k - 1) / 2, g2 = k * (3 * k + 1) / 2;
		if (g1 > i) break;
		ll s = dp[i - g1] + (g2 <= i ? dp[i - g2] : 0);
		dp[i] = (dp[i] + (k % 2 ? s : MOD - s % MOD)) % MOD;
	}
	return dp;
}
