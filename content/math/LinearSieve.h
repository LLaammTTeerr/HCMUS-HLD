/**
 * Author: HCMUS-HLD
 * Description: Linear sieve for all $x < $ MAXN: Mobius u, number of
 * divisors numd, Euler phi, and cnt = exponent of the smallest prime.
 * Time: O(MAXN)
 */
#pragma once

const int MAXN = 1e6 + 5;
int u[MAXN], numd[MAXN], phi[MAXN], cnt[MAXN];
bool isComp[MAXN];
vi primes;
void linearSieve() {
	u[1] = numd[1] = phi[1] = 1;
	rep(i,2,MAXN) {
		if (!isComp[i]) {
			primes.push_back(i);
			u[i] = -1, numd[i] = 2, phi[i] = i - 1, cnt[i] = 1;
		}
		for (int p : primes) {
			if ((ll)i * p >= MAXN) break;
			int x = i * p;
			isComp[x] = 1;
			if (i % p == 0) {
				u[x] = 0, cnt[x] = cnt[i] + 1;
				numd[x] = numd[i] / (cnt[i] + 1) * (cnt[i] + 2);
				phi[x] = phi[i] * p;
				break;
			}
			u[x] = -u[i], numd[x] = numd[i] * 2;
			phi[x] = phi[i] * (p - 1), cnt[x] = 1;
		}
	}
}
