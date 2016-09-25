#pragma once
#include <core/memory/allocator.h>
#include <core/memory/dlmalloc.h>

class HeapAllocator : public Allocator
{
public:
	HeapAllocator(const char *name, size_t initial_size, Allocator *backing);
	~HeapAllocator();

	void *allocate_size(size_t size, size_t alignment) override;
	void free(void *p) override;

	Allocator *backing() { return _backing; }
private:
	Allocator *_backing;
	mspace _msp;
};