#include "Utils.h"

void* utils::get_abs_address(uintptr_t address, int offset, int size)
{
	if (!address) {
		log("[%s] address is null !\n", __func__ );
	}

	DWORD iOffset = *(DWORD*)(address + offset);
	DWORD_PTR ptr = address + iOffset + size;

	if (offset > 0xF0000000) {
		ptr -= 0x100000000;
	}

	return (void*)ptr;
}
