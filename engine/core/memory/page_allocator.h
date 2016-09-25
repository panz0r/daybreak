#pragma once
#include <core/memory/allocator.h>

class PageAllocator : public Allocator
{
public:
	PageAllocator(const char *name);
	~PageAllocator();

	void *allocate_size(size_t size, size_t alignment) override;
	void free(void *p) override;

private:
	size_t _small_page_size;
	size_t _large_page_size;
};