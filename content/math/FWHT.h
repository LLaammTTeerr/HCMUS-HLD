#pragma once

void FWHT(int *f, int type = 1) {
    for (int o = 2, k = 1; o <= limit; o <<= 1, k <<= 1) {
      	for (int i = 0; i < limit; i += o) {
        	for (int j = 0; j < k; j++) {
          		int x = f[i + j], y = f[i + j + k];
          		f[i + j] = x + y, f[i + j + k] = x - y;
          		if (type == -1) {
          			f[i + j] >>= 1, f[i + j + k] >>= 1;
        		}
        	}
      	}
    }
}