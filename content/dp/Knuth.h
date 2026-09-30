/**
 * Author: HCMUS-HLD
 * Description: Knuth optimization for
 * dp[i][j] = min_{i<=k<j} dp[i][k] + dp[k+1][j] + C(i, j).
 * Valid when C satisfies the quadrangle inequality
 * C(a,c)+C(b,d) <= C(a,d)+C(b,c) (a<=b<=c<=d) and is monotone
 * on inclusion; then opt[i][j-1] <= opt[i][j] <= opt[i+1][j].
 * base[i] = dp[i][i]. 0-indexed.
 * Time: O(N^2)
 */
#pragma once

template<class F> ll knuth(int n, vector<ll> base, F C) {
	vector<vector<ll>> dp(n, vector<ll>(n));
	vector<vi> opt(n, vi(n));
	rep(i,0,n) dp[i][i] = base[i], opt[i][i] = i;
	for (int i = n - 2; i >= 0; --i) rep(j,i+1,n) {
		ll mn = LLONG_MAX, c = C(i, j);
		for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); ++k)
			if (dp[i][k] + dp[k+1][j] + c <= mn)
				mn = dp[i][k] + dp[k+1][j] + c, opt[i][j] = k;
		dp[i][j] = mn;
	}
	return dp[0][n-1];
}
