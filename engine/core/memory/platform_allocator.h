#pragma once

namespace platform
{

enum MemoryFlags
{
	MEM_FLAG_NONE,
};

enum PageProtectFlags
{
	PROTECT_READWRITE = 0x1,
	PROTECT_READONLY  = 0x2,
	PROTECT_WRITEONLY = 0x4,
};

// Reserves and commits pages
void *alloc_pages(void *address, size_t size, MemoryFlags flags = MEM_FLAG_NONE);
void free_pages(void *address, size_t size);
void *reserve_pages(void *address, size_t size, MemoryFlags flags = MEM_FLAG_NONE);
void *commit_pages(void *address, size_t size, MemoryFlags flags = MEM_FLAG_NONE);
void decommit_pages(void *address, size_t size);

void *allocate_physical_pages(size_t size);
void deallocate_physical_pages(void *p);
void *map_physical_pages(void *physical_address, size_t size, void *virtual_address, PageProtectFlags flags = PROTECT_READWRITE);


size_t small_page();
size_t large_page();

}