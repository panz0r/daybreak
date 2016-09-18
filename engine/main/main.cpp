#include <Windows.h>


#include <core/memory/page_allocator.h>
#include <core/memory/dlmalloc.h>

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
	)
{

	PageAllocator *allocator = new PageAllocator("base");

	PageAllocator* alloc3 = MAKE_NEW(*allocator, PageAllocator, "hej");
	PageAllocator* alloc4 = MAKE_NEW(*allocator, PageAllocator, "hej");
	
	auto mspace = create_mspace(0, 0);
	void *p1 = mspace_malloc(mspace, 1024);
	void *p2 = mspace_malloc(mspace, 1024);
	void *p3 = mspace_malloc(mspace, 1024);
	void *p4 = mspace_malloc(mspace, 1024);


	return 0;
}