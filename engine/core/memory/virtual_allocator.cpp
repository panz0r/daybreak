#include <core/memory/virtual_allocator.h>
#include <core/memory/platform_allocator.h>
#include <core/memory/memory_utils.h>


VirtualAllocator::VirtualAllocator()
{

}

VirtualAllocator::~VirtualAllocator()
{

}


void *VirtualAllocator::allocate_with_readonly_area(size_t size)
{
	
	void *physical_pages = platform::allocate_physical_pages(size);
	void *va1 = platform::reserve_pages(nullptr, size);
	void *va2 = platform::reserve_pages(read_only_ptr(va1), size);
	platform::free_pages(va1, 0);
	platform::free_pages(va2, 0);
	va1 = platform::map_physical_pages(physical_pages, size, va1);
	va2 = platform::map_physical_pages(physical_pages, size, va2, platform::PROTECT_READONLY);

	// TODO, store physical address so it can be deallocated

	return va1;
}

void *VirtualAllocator::allocate_with_loopback(size_t size, unsigned loop_count)
{
	// 64k min granularity
	size = align_ptr(size, 1024*64);

	void *phyical_pages = platform::allocate_physical_pages(size);
	bool mapped = false;
	void *virtual_address = nullptr;
	do
	{
		virtual_address = platform::reserve_pages(nullptr, size * loop_count);
		platform::free_pages(virtual_address, 0);
		mapped = true;
	
		void *next_va = virtual_address;
		for (unsigned i = 0; i < loop_count; ++i)
		{
			if (!platform::map_physical_pages(phyical_pages, size, next_va)) {
				mapped = false;
				break;
			}
			next_va = offset_ptr(next_va, size);
		}
	} while(!mapped);

	// TODO, store physical address so it can be deallocated
	return virtual_address;
}
