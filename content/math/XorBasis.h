#pragma once

struct Node {
    int basis[MAXLOG], szBasis, basisMask;

    Node() {
        szBasis = basisMask = 0;
        memset(basis, 0, sizeof(basis));
    }

    bool insertVector(int mask, int idx) {
        while(mask > 0) {
            int i = 31 - __builtin_clz(mask);
            if(!basis[i]) {
                ++szBasis, basis[i] = mask;
                basisMask |= (1 << i);
                return true;
            }
            mask ^= basis[i];
        }
        return false;
    }

    bool checkVector(int mask) const {
        while(mask > 0) {
            int i = 31 - __builtin_clz(mask);
            if(!basis[i]) return false;
            mask ^= basis[i];
        }
        return true;
    }

    Node mergeNode(const Node &A) {
        Node res(*this);
        int mask = A.basisMask;
        while(mask > 0) {
            int i = 31 - __builtin_clz(mask);
            res.insertVector(A.basis[i]);
            mask ^= (1 << i);
        }

        return res;
    }

    // find k-th element from small to big in Basis
    int query(int k) const { // 1-indexed
        int mask = 0, tot = 1 << szBasis, fMask = basisMask;
        while(fMask > 0) {
            int i = 31 - __builtin_clz(fMask), low(tot >> 1);
            if(low < k && !(mask >> i & 1) || low >= k && (mask >> i & 1)) mask ^= basis[i];
            if(low < k) k -= low;
            fMask ^= (1 << i), tot >>= 1;
        }
        return mask;
    }

    int getValPos(int mask) const { // 1-indexed, if mask < 0, result = 0
        if(mask < 0) return 0;
        int firstMask = mask, fMask = basisMask, tot(1 << szBasis), cnt(1);
        while(fMask > 0) {
            int i = 31 - __builtin_clz(fMask), low(tot >> 1);
            if(firstMask >> i & 1) cnt += low, mask ^= basis[i];
            fMask ^= (1 << i), tot >>= 1;
        }
        return cnt;
    }

    int getMax(void) const {
        int res = 0, mask = basisMask;
        while(mask > 0) {
            int i = 31 - __builtin_clz(mask);
            if(!(res >> i & 1)) res ^= basis[i];
            mask ^= (1 << i);
        }
        return res;
    }
}