/**
 * Author: HCMUS-HLD
 * Description: Duval: prints the Lyndon factorization of s
 * (non-increasing sequence of Lyndon words).
 * Time: O(N)
 */
#pragma once
void lyndon(string s) {
	int n = (int) s.length();
	int i = 0;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j]) k = i;
			else ++k;
			++j;
		}
		while (i <= k) {
			cout << s.substr(i, j - k) << ' ';
			i += j - k;
		}
	}
	cout << endl;
}