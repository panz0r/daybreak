#include <core/memory/page_allocator.h>
#include <core/memory/platform_allocator.h>

PageAllocator::PageAllocator(const char* name)
	: Allocator(name)
{
	_large_page_size = platform::large_page();
	_small_page_size = platform::small_page();
}

PageAllocator::~PageAllocator()
{
}

void *PageAllocator::allocate_size(size_t size, size_t alignment)
{
	return platform::alloc_pages(nullptr, size, platform::MEM_FLAG_NONE);
}

void PageAllocator::free(void *p)
{
	platform::free_pages(p, 0);
}
