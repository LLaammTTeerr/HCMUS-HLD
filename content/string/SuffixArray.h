/**
 * Author: HCMUS-HLD
 * Description: 0-indexed suffix array. Set str, strLen =
 * sz(str), call buildSA(). sa[i] = start of i-th smallest
 * suffix, pos = inverse of sa, lcp[i] = LCP(sa[i], sa[i+1]).
 * Needs str[strLen] to be a unique terminator (std::string
 * gives a NUL char).
 * Time: $O(N \log^2(N))$
 */
#pragma once

namespace SuffixArray {
	const int MAXN = 500005;
	string str; int strLen;
	int sa[MAXN], pos[MAXN], lcp[MAXN], tmp[MAXN], gap;
	bool sufCmp(int i, int j) {
		if(pos[i] != pos[j]) return (pos[i] < pos[j]);
		return (max(i, j) + gap < strLen) ? (pos[i + gap] < pos[j + gap]) : (i > j);
	}
	 
	void buildLCP(void) {
		int k(0);
		for (int i = 0; i < strLen; ++i) {
			if(pos[i] != strLen - 1) {
				for (int j = sa[pos[i] + 1]; str[i + k] == str[j + k]; ) ++k;
				lcp[pos[i]] = k, k -= bool(k);
			}
		}
	}

	void buildSA(void) {
		for (int i = 0; i < strLen; ++i) sa[i] = i, pos[i] = str[i];
		for (gap = 1; ; gap <<= 1) {
			sort(sa, sa + strLen, sufCmp);
			for (int i = 0; i + 1 < strLen; ++i)
				tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
			for (int i = 0; i < strLen; ++i) pos[sa[i]] = tmp[i];
			if(tmp[strLen - 1] == strLen - 1) break;
		}
		buildLCP();
	}
}