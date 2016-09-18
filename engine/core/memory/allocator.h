#pragma once
#include <new>

class Allocator
{
public:
	Allocator(const char *name);
	virtual ~Allocator() {}
	
	virtual void *allocate_size(size_t size, size_t alignment) = 0;
	virtual void free(void *p) = 0;
	
	template <class T, class ...ARGS>
	inline T* make_new(ARGS... args) { return new( allocate_size(sizeof(T), alignof(T)) ) T(args...); }

	const char *name() const { return _name; }
private:
	char _name[32];
};

#define MAKE_NEW(allocator, T, ...) (allocator).make_new<T>(__VA_ARGS__); 