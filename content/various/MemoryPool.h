#pragma once

template<class T, int MAX>
class MemoryPool {
private:
  std::array<std::byte, sizeof(T) * MAX> buffer;
  std::pmr::monotonic_buffer_resource resource;
  std::pmr::polymorphic_allocator<T> allocator;
public:
  MemoryPool(void): resource(buffer.data(), buffer.size()), allocator(&resource) {}

  T *allocate(const T& val = T()) {
    T *p = allocator.allocate(1);
    allocator.construct(p, val);
    return p;
  }
};