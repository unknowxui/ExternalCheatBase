#include <iostream>

#include "Memory/MemoryManager.h"

int main()
{
    g_memManager.target_process("dota2.exe");
    int wB = 0x48;
    std::cout << std::hex << g_memManager.read_process_memory<int>((void*)0x7FF65463167A);
}
