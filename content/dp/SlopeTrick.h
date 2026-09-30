/**
 * Author: HCMUS-HLD
 * Description: Slope trick example: minimum total |change|
 * (+1/-1 operations) to make A strictly increasing. For
 * non-decreasing, drop the "- i". The multiset holds the
 * breakpoints of the convex function; its max is the argmin.
 * Time: O(N \log N)
 */
#pragma once

ll slopeTrick(const vector<ll>& A) {
	multiset<ll> pts; ll ans = 0;
	rep(i,0,sz(A)) {
		ll a = A[i] - i;
		pts.insert(a);
		ll opt = *pts.rbegin();
		if (a < opt) {
			pts.erase(prev(pts.end()));
			pts.insert(a), ans += opt - a;
		}
	}
	return ans;
}
