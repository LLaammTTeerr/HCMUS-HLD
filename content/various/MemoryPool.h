/**
 * Author: HCMUS-HLD
 * Description: Fast allocation of up to MAX objects of type T from
 * a static buffer; memory is never freed. Beyond MAX it silently
 * falls back to the heap. The pool holds sizeof(T)*MAX bytes, so
 * declare it global/static. Needs GCC 9+ (memory\_resource).
 * Usage: MemoryPool<Node, 1<<20> pool; Node* x = pool.allocate();
 * Time: O(1)
 */
#pragma once

template<class T, int MAX>
struct MemoryPool {
	array<byte, sizeof(T) * MAX> buffer;
	pmr::monotonic_buffer_resource resource;
	pmr::polymorphic_allocator<T> allocator;
	MemoryPool() : resource(buffer.data(), buffer.size()),
		allocator(&resource) {}
	T* allocate(const T& val = T()) {
		T* p = allocator.allocate(1);
		allocator.construct(p, val);
		return p;
	}
};
