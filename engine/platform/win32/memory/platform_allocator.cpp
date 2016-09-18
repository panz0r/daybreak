#include <core/memory/platform_allocator.h>
#include <windows.h>

namespace platform
{

unsigned _additional_flags[Flags::FLAG_COUNT] =
{
	0,
	MEM_LARGE_PAGES
};

void *alloc_pages(void *address, size_t size, Flags flags)
{
	unsigned additional_flags = _additional_flags[flags];
	return VirtualAlloc(address, size, MEM_RESERVE | MEM_COMMIT | additional_flags, PAGE_READWRITE);
}

void free_pages(void *address, size_t size)
{
	VirtualFree(address, 0, MEM_RELEASE);
}

void *reserve_pages(void *address, size_t size, Flags flags)
{
	unsigned additional_flags = _additional_flags[flags];
	return VirtualAlloc(address, size, MEM_RESERVE | additional_flags, PAGE_READWRITE);
}

void *commit_pages(void *address, size_t size, Flags flags)
{
	unsigned additional_flags = _additional_flags[flags];
	return VirtualAlloc(address, size, MEM_COMMIT | additional_flags, PAGE_READWRITE);
}

void decommit_pages(void *address, size_t size)
{
	VirtualFree(address, size, MEM_DECOMMIT);	
}

size_t small_page()
{
	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
	return static_cast<size_t>(system_info.dwPageSize);
}

size_t large_page()
{
	return GetLargePageMinimum();
}


} // namespace platform