#pragma once

namespace platform
{

enum Flags
{
	NONE, LARGE_PAGES, FLAG_COUNT
};

// Reserves and commits pages
void *alloc_pages(void *address, size_t size, Flags flags = NONE);
void free_pages(void *address, size_t size);
void *reserve_pages(void *address, size_t size, Flags flags = NONE);
void *commit_pages(void *address, size_t size, Flags flags = NONE);
void decommit_pages(void *address, size_t size);

size_t small_page();
size_t large_page();

}