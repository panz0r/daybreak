#include <core/memory/page_allocator.h>
#include <core/memory/platform_allocator.h>

PageAllocator::PageAllocator(const char* name)
	: Allocator(name)
{
}

PageAllocator::~PageAllocator()
{
}

void *PageAllocator::allocate_size(size_t size, size_t alignment)
{
	return platform::alloc_pages(nullptr, size, platform::NONE);
}

void PageAllocator::free(void *p)
{
	platform::free_pages(p, 0);
}

