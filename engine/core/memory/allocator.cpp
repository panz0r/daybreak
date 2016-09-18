#include <core/memory/allocator.h>
#include <string>

Allocator::Allocator(const char *name)
{
	{ strcpy_s<32>(_name, name); }
}