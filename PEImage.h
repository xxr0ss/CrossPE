#pragma once
#include <Windows.h>

#define PEHEADER_SIZE (0x1000)
#define ALIGN_SIZE_UP(Size, Alignment) (((ULONG_PTR)(Size) + Alignment - 1) & ~(Alignment - 1))
#define MEM_OFFSET(EndAddr, StartAddr)((ULONG)((ULONG_PTR)EndAddr - (ULONG_PTR)StartAddr))


class PEImage {
public:
	DWORD dwPageSize;
	HANDLE hFile;
	HANDLE hProc;
	WORD sectionCount;
	

	PBYTE hModule;
	// Structures:
	PIMAGE_DOS_HEADER DosHeader;
	PIMAGE_NT_HEADERS

};
