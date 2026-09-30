/* Usage: faster and shorter segment tree

*/

namespace SegTree {
    int seg[2 * MAXN], nTree;
    void modify(int p, int val) { // set value at position p
        seg[p += nTree] = val;
        for (; p > 1; p >>= 1) seg[p >> 1] = seg[p] + seg[p ^ 1];
    }
    int query(int l, int r) {
        int res = 0;
        for (l += nTree, r += nTree; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res += seg[l++];
            if(r & 1) res += seg[--r];
        }
        return res;
    }
    void build(int n, int a[]) {
        nTree = n;
        for (int i = 1; i <= n; ++i) seg[n + i - 1] = a[i]; // leaf node contains position i
        for (int i = n - 1; i > 0; --i) seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }
}