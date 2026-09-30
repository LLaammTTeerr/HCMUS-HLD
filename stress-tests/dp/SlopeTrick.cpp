#include "../utilities/template.h"
#include "../../content/dp/SlopeTrick.h"

int main() {
	mt19937 rng(13);
	rep(it,0,3000) {
		int n = 1 + rng() % 12;
		vector<ll> A(n);
		for (ll& x : A) x = (ll)(rng() % 21) - 10;
		// brute: B_i = A_i - i non-decreasing; optimal values lie in
		// {A_j - j}
		vector<ll> cand;
		rep(i,0,n) cand.push_back(A[i] - i);
		sort(all(cand));
		int m = sz(cand);
		vector<ll> dp(m, 0);
		rep(i,0,n) {
			vector<ll> nd(m);
			ll best = LLONG_MAX;
			rep(v,0,m) {
				best = min(best, dp[v]);
				nd[v] = best + abs(A[i] - i - cand[v]);
			}
			dp = nd;
		}
		assert(slopeTrick(A) == *min_element(all(dp)));
	}
	assert(slopeTrick({}) == 0);
	cout << "Tests passed!" << endl;
}
