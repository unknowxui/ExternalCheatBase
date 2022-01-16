#pragma once
#include <map>

#include "../Utils/Utils.h"


class MemoryManager
{
public:
	void target_process(const char* procName);


	std::pair<void*, unsigned long> get_module_info(const char* modulName);
	DWORD get_process_id_by_name(const char* processName);


	void write_process_memory(void* address, void* wBuffer, size_t size);

	template<typename T>
	T read_process_memory(void* address);

	__forceinline bool is_target() { return m_bIsProcHandleOpen; }

private:
	HANDLE m_hTargetProcessHandle;
	bool m_bIsProcHandleOpen = false;
};

extern MemoryManager g_memManager;

template<typename T>
T MemoryManager::read_process_memory(void* address)
{
	if (!is_target()) return (T)0;

	T outBuffer;

	if (ReadProcessMemory(m_hTargetProcessHandle, address, &outBuffer, sizeof(T), 0)) {
		return outBuffer;
	}

	return (T)0;
}
