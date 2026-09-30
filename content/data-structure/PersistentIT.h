/**
 * Author: HCMUS-HLD
 * Description: Persistent segment tree of counts over
 * positions 1..n. init(n); root 0 is the empty version;
 * newRoot = update(oldRoot, pos, val) adds val at pos;
 * queryCnt(root, u, v) sums [u, v]. k-th smallest in a
 * range: walk roots r[R] and r[L-1] together.
 * Time: O(\log N) per operation, O(\log N) new nodes.
 */
#pragma once

namespace PersistentSeg {
	const int MAXN = 200005;
	struct SegNode {
		int cnt, L, R;
	} seg[50 * MAXN];

	int nNode, nTree;

	void init(int _n) { nNode = _n, nTree = 0; }
	
	int update(int oldID, int l, int r, int pos, int val) {
		if(l == r) {
			seg[++nTree] = seg[oldID], seg[nTree].cnt += val;
			return nTree;
		}
		int cur(++nTree), mid = (l + r) >> 1;
		seg[cur] = seg[oldID];
		if(pos <= mid) {
			seg[cur].L = update(seg[oldID].L, l, mid, pos, val);
		} else {
			seg[cur].R = update(seg[oldID].R, mid + 1, r, pos, val);
		}
		seg[cur].cnt = seg[seg[cur].L].cnt + seg[seg[cur].R].cnt;
		return cur;
	}

	int update(int oldID, int pos, int val) {
		return update(oldID, 1, nNode, pos, val);
	}
	
	int queryCnt(int id, int l, int r, int u, int v) {
		if(u <= l && r <= v) return seg[id].cnt;
		int res = 0, mid = (l + r) >> 1;
		if(mid >= u) res += queryCnt(seg[id].L, l, mid, u, v);
		if(mid + 1 <= v) res += queryCnt(seg[id].R, mid + 1, r, u, v);
		return res;
	}

	int queryCnt(int id, int u, int v) {
		return queryCnt(id, 1, nNode, u, v);
	}
};