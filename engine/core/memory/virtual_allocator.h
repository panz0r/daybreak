#pragma once

class VirtualAllocator
{
public:
	VirtualAllocator();
	~VirtualAllocator();
	
	void *allocate_with_readonly_area(size_t size);
	void *allocate_with_loopback(size_t size, unsigned loop_count);

private:
};


