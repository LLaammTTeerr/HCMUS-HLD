template <typename T>
T inverse_modulo(T a, T m) {
	T u = 0, v = 1;
	while (a > 0) {
		T t = m / a;
		m -= t * a; std::swap(a, m);
		u -= t * v; std::swap(u, v);
	}
	assert(m == 1);
	return u;
}