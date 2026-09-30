/**
 * Author: HCMUS-HLD
 * Description: Block-cut tree, vertices 1..n (num[0] is the
 * timer). Globals: adj[], num[], low[],
 * lastComp[], stack<int> st, numNode, numBCC, adjp[] (size
 * numNode + #blocks). Block i is node numNode + i, adjacent to
 * its vertices. Call tarjan(u) for each unvisited u; isolated
 * vertices get no block.
 * Time: $O(V + E)$
 */
#pragma once

void tarjan(int u) {
	low[u] = num[u] = ++num[0];
	for (int it = 0; it < int(adj[u].size()); ++it) {
		int v(adj[u][it]);
		if(!num[v]) {
			st.push(u); tarjan(v);
			low[u] = min(low[u], low[v]);
			if(low[v] == num[u]) {
				lastComp[u] = ++numBCC;
				adjp[u].push_back(numNode + numBCC);
				do {
					v = st.top(); st.pop();
					if(lastComp[v] != numBCC) {
						lastComp[v] = numBCC;
						adjp[numNode + numBCC].push_back(v);
					}
				} while(v != u);
			}
		} else { low[u] = min(low[u], num[v]); }
	}
	st.push(u);
}