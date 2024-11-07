/**
 * Author: Phan Binh Nguyen Lam
 * Date: 2011-11-29
 * License: CC0
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by negative numbers.
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.add_disjunction(a, b); // a or b
 * Time: O(N+E)
 */
#pragma once

class TwoSat {
private:
	int n, no;
	int* comp;
	bool* was;
	std::vector <int>* g;
	std::vector <int>* g_t;
	std::vector <int> topo;

	void add_edge(int u, int v) {
		g[u].push_back(v);
		g_t[v].push_back(u);
	}

	void dfs_topo(int u) {
		was[u] = 1;
		for (int v : g[u])
			if (not was[v])
				dfs_topo(v);
		topo.push_back(u);
	}

	void dfs_scc(int u) {
		for (int v : g_t[u]) if (not comp[v]) {
			comp[v] = comp[u];
			dfs_scc(v);
		}
	}
public:
	TwoSat(int _n = 0) : n(_n), no(0) {
		topo.reserve(2 * n);
		comp = new int [2 * n + 1];
		g = new std::vector <int> [2 * n + 1];
		g_t = new std::vector <int> [2 * n + 1];
		was = new bool [2 * n + 1];

		comp += n;
		g += n;
		g_t += n;
		was += n;
	}

	void add_disjunction(int u, int v) {
		add_edge(-u, v);
		add_edge(-v, u);
	}

	std::vector <int>* solve(void) {
		for (int i = 1; i <= n; i += 1) {
			if (not was[i])
				dfs_topo(i);
			if (not was[-i])
				dfs_topo(-i);
		}
		std::reverse(topo.begin(), topo.end());
		for (int u : topo) {
			if (not comp[u]) {
				comp[u] = ++no;
				dfs_scc(u);
			}
		}
		std::vector <int>* ans = new std::vector <int> (n + 1);
		for (int i = 1; i <= n; i += 1) {
			int x = comp[i], y = comp[-i];
			if (x == y)
				return nullptr;
			(*ans)[i] = x > y;
		}
		return ans;
	}
};