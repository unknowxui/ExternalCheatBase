#include "MemoryManager.h"

MemoryManager g_memManager;

void MemoryManager::target_process(const char* procName)
{
	this->m_hTargetProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->get_process_id_by_name(procName));
	if (m_hTargetProcessHandle == INVALID_HANDLE_VALUE) {
		m_bIsProcHandleOpen = false;
		log("[%s] m_hTargetProcessHandle is INVALID_HANDLE_VALUE, process name = %s\n", __func__, procName);
	}

	m_bIsProcHandleOpen = true;
	log("%s handle open ! \n", procName);
}

//=============================================================================================
std::pair<void*, unsigned long> MemoryManager::get_module_info(const char* modulName)
{
	if (!is_target()) {
		log("[%s] m_hTargetProcessHandle is INVALID_HANDLE_VALUE \n", __func__);

		return std::pair<void*, unsigned long>(nullptr, 0);
	}

	HMODULE targetModuleHandle = GetModuleHandleA(modulName);
	if (targetModuleHandle == INVALID_HANDLE_VALUE) {
		log("[%s] targetModuleHandle is INVALID_HANDLE_VALUE \n", __func__);

		return std::pair<void*, unsigned long>(nullptr, 0);
	}

	MODULEINFO moduleInfo = { 0 };
	GetModuleInformation(m_hTargetProcessHandle, targetModuleHandle, &moduleInfo, sizeof(moduleInfo));

	return std::pair<void*, unsigned long>(moduleInfo.lpBaseOfDll, moduleInfo.SizeOfImage);
}
//=============================================================================================
DWORD MemoryManager::get_process_id_by_name(const char* processName)
{
	HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if (snapShot == INVALID_HANDLE_VALUE) {
		log("[%s] snapShot is INVALID_HANDLE_VALUE \n", __func__);
		return 0;
	}

	PROCESSENTRY32 pEntry = { 0 };
	pEntry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapShot, &pEntry)) {
		if (!strcmp(pEntry.szExeFile, processName)) {
			return pEntry.th32ProcessID;
		}
	}

	while (Process32Next(snapShot, &pEntry)) {
		if (!strcmp(pEntry.szExeFile, processName)) {
			return pEntry.th32ProcessID;
		}
	}

	log("Process %s not found !\n", processName);
	return 0;
}
//=============================================================================================
void MemoryManager::write_process_memory(void* address, void* wBuffer, size_t size)
{
	if (!is_target()) return;

	if (!WriteProcessMemory(m_hTargetProcessHandle, address, wBuffer, size, 0)) {
		log("Memory is not write! %p %p %i\n",address,wBuffer,size);
	}
}
//=============================================================================================

//=============================================================================================