#include "../utilities/template.h"
#include "../../content/combination/PartitionNumbers.h"

int main() {
	const ll M = 998244353;
	int n = 3000;
	// O(n^2) coin DP
	vector<ll> dp(n + 1);
	dp[0] = 1;
	rep(k,1,n+1) rep(i,k,n+1) dp[i] = (dp[i] + dp[i - k]) % M;
	assert(partitions(n) == dp);
	vector<ll> exact = partitions(100, (ll)4e18); // exact values fit
	assert(exact[0] == 1 && exact[5] == 7 && exact[20] == 627 && exact[100] == 190569292);
	assert(partitions(0) == vector<ll>{1});
	vector<ll> q = partitions(1000, 1000000007);
	vector<ll> dq(1001);
	dq[0] = 1;
	rep(k,1,1001) rep(i,k,1001) dq[i] = (dq[i] + dq[i - k]) % 1000000007;
	assert(q == dq);
	cout << "Tests passed!" << endl;
}
