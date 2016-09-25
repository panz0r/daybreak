#include <Windows.h>


#include <core/memory/page_allocator.h>
#include <core/memory/heap_allocator.h>
#include <core/memory/platform_allocator.h>
#include <core/memory/virtual_allocator.h>
#include <core/memory/memory_utils.h>

#include <core/memory/dlmalloc.h>

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
	)
{

	PageAllocator *allocator = new PageAllocator("base");
	HeapAllocator *heap = new HeapAllocator("heap", 2*1024*1024, allocator);
	VirtualAllocator *va = new VirtualAllocator();
	auto ar1 = heap->allocate_size(34, 4);
	auto ar2 = heap->allocate_size(892, 4);
	auto ar3 = heap->allocate_size(99892, 4);

	//void *physical = platform::allocate_physical_pages(4096);
	//void *va1 = platform::reserve_pages(nullptr, 4096);
	//size_t tb = (1024ULL*(1024ULL*(1024ULL*(1024ULL))));
	//void *va2 = reinterpret_cast<void*>(reinterpret_cast<size_t>(va1) + tb);
	//va2 = platform::reserve_pages(va2, 4096);

	//platform::free_pages(va1, 0);
	//platform::free_pages(va2, 0);
	//va1 = platform::map_physical_pages(physical, 4096, va1);
	//va2 = platform::map_physical_pages(physical, 4096, va2, platform::PROTECT_READONLY);

	//unsigned *uin1 = reinterpret_cast<unsigned*>(va1);
	//unsigned *uin2 = reinterpret_cast<unsigned*>(va2);

	//*uin1 = 0x1337;

	//unsigned r = *uin2;

	//*uin2 = 0xb00b;
	
	void *rw_p = va->allocate_with_readonly_area(4096);
	void *ring = va->allocate_with_loopback(65534, 3);

	(*(unsigned*)rw_p) = 0x1337;
	unsigned *ro_p = (unsigned*)read_only_ptr(rw_p);
	*ro_p = 1;

	return 0;
}