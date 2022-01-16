#pragma once
#include <Windows.h>

class DriverManager
{
public:
	DriverManager();

	void write_process_memory(void* address, void* wBuffer, size_t size);
	void read_process_memory(void* address, void* oBuffer, size_t size);

private:
	HANDLE m_hDriver;
};

