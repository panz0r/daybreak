#pragma once

//#include <core/memory/allocator.h>

class Allocator;
class HeapAllocator;
class PageAllocator;

namespace memory_internal
{
	Allocator *_default_page_allocator;
	Allocator *_default_heap_allocator;
}


namespace memory_globals
{

inline Allocator &default_page_allocator() { return *memory_internal::_default_page_allocator; }
inline Allocator &default_heap_allocator() { return *memory_internal::_default_heap_allocator; }

}