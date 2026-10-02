/**
 * Author: HCMUS-HLD
 * Description: z[i] = length of the longest common prefix of s
 * and s[i..], with z[0] = n. To find pattern P in T run on
 * P + "\#" + T and look for z[i] = |P|.
 * Time: O(N)
 */
#pragma once

vi Z(const string& s) {
	int n = sz(s);
	vi z(n);
	if (n) z[0] = n;
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i < r) z[i] = min(r - i, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] > r) l = i, r = i + z[i];
	}
	return z;
}
