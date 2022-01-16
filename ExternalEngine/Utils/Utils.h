#pragma once
#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>

#include "../Defs.h"

namespace utils
{
	void* get_abs_address(uintptr_t address, int offset, int size);
};

