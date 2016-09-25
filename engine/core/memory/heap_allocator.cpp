#include <core/memory/heap_allocator.h>
#include <core/memory/dlmalloc.h>

HeapAllocator::HeapAllocator(const char *name, size_t initial_size, Allocator *backing)
	: Allocator(name), _backing(backing)
{
	auto mmap = [](size_t size, void *userdata)
	{
		HeapAllocator *self = reinterpret_cast<HeapAllocator*>(userdata);
		auto ar = self->_backing->allocate_size(size, Allocator::DEFAULT_ALIGNMENT);
		return ar;
	};

	auto munmap = [](void *p, size_t size, void *userdata)
	{
		HeapAllocator *self = reinterpret_cast<HeapAllocator*>(userdata);
		self->_backing->free(p);
		return 0;
	};

	auto base = _backing->allocate_size(initial_size, Allocator::DEFAULT_ALIGNMENT);
	_msp = create_mspace_with_base(base, initial_size, 0, mmap, munmap, this);

}

HeapAllocator::~HeapAllocator()
{

}

void *HeapAllocator::allocate_size(size_t size, size_t alignment)
{
	return mspace_memalign(_msp, alignment, size);
}

void HeapAllocator::free(void *p)
{
	mspace_free(_msp, p);
}
