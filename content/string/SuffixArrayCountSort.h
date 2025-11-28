/**
 * Time: $O(N \log(N))$
*/

namespace SuffixArray {
    int cnt[MAXN], tmp[MAXN], gap;
    
    bool sufCmp(int u, int v) // check SuffixArray.h
    void buildLCP(void) // check SuffixArray.h
    
    void countsort(int k) {
        for (int i = 0; i <= max(256, strLen); ++i) cnt[i] = 0;
        for (int i = 1; i <= strLen; ++i) ++cnt[(i + k <= strLen ? pos[i + k] : 0)];
        for (int i = 1; i <= max(256, strLen); ++i) cnt[i] += cnt[i - 1];
        for (int i = strLen; i > 0; --i) tmp[cnt[(sa[i] + k <= strLen ? pos[sa[i] + k] : 0)]--] = sa[i];
        for (int i = 1; i <= strLen; ++i) sa[i] = tmp[i];
    }
    
    void buildSA(void) {
        for (int i = 1; i <= strLen; ++i) sa[i] = i, pos[i] = str[i];
        for (gap = 1; gap <= strLen; gap <<= 1) {
            countsort(gap), countsort(0);
            tmp[sa[1]] = 1;
            for (int i = 2; i <= strLen; ++i) tmp[sa[i]] = tmp[sa[i - 1]] + sufCmp(sa[i - 1], sa[i]);
            for (int i = 1; i <= strLen; ++i) pos[i] = tmp[i];
        }
        buildLCP();
    }
}