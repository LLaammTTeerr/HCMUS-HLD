/**
 * Author: HCMUS-HLD
 * Description: Prefix function, 1-indexed: str[0] is a dummy
 * char, lps[i] = longest proper border of str[1..i]. To find
 * pattern P in T run on " " + P + "\#" + T.
 * Time: O(N)
 */
#pragma once

vi kmp(const string &str) {
	int n = sz(str) - 1; vi lps(n + 1);
	for (int i = 2; i <= n; ++i) {
		int k = lps[i - 1];
		while(k > 0 && str[k + 1] != str[i]) k = lps[k];
		lps[i] = k + (str[k + 1] == str[i]);
	}
	return lps;
}
