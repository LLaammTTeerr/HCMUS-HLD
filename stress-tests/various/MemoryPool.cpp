#include "../utilities/template.h"

#include "../../content/various/MemoryPool.h"

struct Node { int v = 7; ll w = 5; Node* nxt = 0; };
MemoryPool<Node, 1000> pool;

int main() {
	set<Node*> seen;
	char* lo = (char*)pool.buffer.data();
	char* hi = lo + pool.buffer.size();
	rep(i,0,1500) {
		Node* p = i % 2 ? pool.allocate() : pool.allocate(Node{i, -i, 0});
		assert(seen.insert(p).second); // distinct
		if (i % 2) assert(p->v == 7 && p->w == 5 && !p->nxt);
		else assert(p->v == i && p->w == -i);
		if (i < 990) assert(lo <= (char*)p && (char*)(p + 1) <= hi);
		p->nxt = p; // writable
	}
	cout << "Tests passed!" << endl;
}
