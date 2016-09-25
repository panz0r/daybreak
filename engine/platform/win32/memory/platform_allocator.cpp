#include <core/memory/platform_allocator.h>
#include <windows.h>
#include <assert.h>

namespace platform
{

inline unsigned allocation_type_flags(MemoryFlags memory_flags)
{
	unsigned allocation_type_flags = 0;
	return allocation_type_flags;
}

void *alloc_pages(void *address, size_t size, MemoryFlags memory_flags)
{
	unsigned additional_flags = allocation_type_flags(memory_flags);
	return VirtualAlloc(address, size, MEM_RESERVE | MEM_COMMIT | additional_flags, PAGE_READWRITE);
}

void free_pages(void *address, size_t size)
{
	VirtualFree(address, 0, MEM_RELEASE);
}

void *reserve_pages(void *address, size_t size, MemoryFlags memory_flags)
{
	unsigned additional_flags = allocation_type_flags(memory_flags);
	return VirtualAlloc(address, size, MEM_RESERVE | additional_flags, PAGE_READWRITE);
}

void *commit_pages(void *address, size_t size, MemoryFlags memory_flags)
{
	unsigned additional_flags = allocation_type_flags(memory_flags);
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

void *allocate_physical_pages(size_t size)
{
	HANDLE handle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE | SEC_COMMIT, 0, (DWORD)size, nullptr);
	assert(handle);
	return handle;
}

void deallocate_physical_pages(void *p)
{
	CloseHandle(p);
}

inline unsigned map_protection(PageProtectFlags flags)
{
	unsigned protect = 0;
	if(flags & PROTECT_READWRITE)
		protect |= FILE_MAP_ALL_ACCESS;
	if(flags & PROTECT_READONLY)
		protect |= FILE_MAP_READ;
	if(flags & PROTECT_WRITEONLY)
		protect |= FILE_MAP_WRITE;
	return protect;
}

void *map_physical_pages(void *physical_address, size_t size, void *virtual_address, PageProtectFlags flags /* = PROTECT_READWRITE */)
{
	unsigned protect = map_protection(flags);
	void *p = MapViewOfFileEx(physical_address, protect, 0, 0, size, virtual_address);
	if (!p) {
		auto err = GetLastError();
	}
	return p;
}



} // namespace platform