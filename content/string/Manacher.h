/**
 * Author: HCMUS-HLD
 * Description: Manacher, 1-indexed. Manacher M(s); then
 * pod[i]: s[i-k..i+k] is a palindrome for k <= pod[i];
 * pev[i]: s[i-k+1..i+k] is a palindrome for k <= pev[i]
 * (even, centred between i and i+1).
 * Time: O(N)
 */
#pragma once

struct Manacher {
int n; string S; vi pod, pev;
Manacher(const string& s) : n(sz(s)), S(" " + s),
	pod(n + 2), pev(n + 2) { calc_pod(); calc_pev(); }

void calc_pod() {
	int L = 1, R = 0;
	for(int i = 1; i <= n; i++) {
		if(i > R) pod[i] = 0;
		else pod[i] = min(R - i, pod[L + (R - i)]);
		while(i - pod[i] - 1 > 0 && i + pod[i] + 1 <= n && S[i - pod[i] - 1] == S[i + pod[i] + 1]) pod[i]++;

		if(i + pod[i] > R) {
			R = i + pod[i];
			L = i - pod[i];
		}
	}
}

void calc_pev() {
	int L = 1, R = 0;
	for(int i = 1; i < n; i++) {
		int j = i + 1;
		if(j > R) pev[i] = 0;
		else pev[i] = min(R - j + 1, pev[L + (R - j)]);
		while(i - pev[i] > 0 && j + pev[i] <= n && S[i - pev[i]] == S[j + pev[i]]) pev[i]++;
		if(i + pev[i] > R) {
			R = i + pev[i];
			L = j - pev[i];
		}
	}
}
};
