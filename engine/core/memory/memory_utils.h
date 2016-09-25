#pragma once

#define KiB 1024ULL
static const size_t _1tb = KiB*KiB*KiB*KiB;

template <typename T>
inline T align_ptr(T p, size_t align) {
	return (T)(((size_t)(p) + (align-1)) & ~(align-1));
}

inline void *offset_ptr(void *p, size_t offset) {
	return reinterpret_cast<void*>(reinterpret_cast<size_t>(p) + offset);
}

inline void *read_only_ptr(void *p) {
	return reinterpret_cast<void*>(reinterpret_cast<size_t>(p) + _1tb);
}
