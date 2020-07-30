#include "PEImage.h"

PBYTE PEImage::loadPEImage(HANDLE hFile) {
	hPEFile = hFile;
	BOOL bResult = FALSE;
	DWORD IoCnt;
	DWORD readOffset = 0;

	do {
		fileSize = GetFileSize(hPEFile, NULL);
		if (fileSize == 0)
			// TODO: 构造提供给窗口的错误信息 下面的也是
			break;

		peImageData = (PBYTE)malloc(fileSize);
		bResult = ReadFile(hPEFile, peImageData, fileSize, &IoCnt, NULL);
		if (closeFileAfterLoading) {
			CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
		}
		if (!bResult)
			break;

		if (!VerifyImage(peImageData))
			break;

		DosHeader = (PIMAGE_DOS_HEADER)peImageData;
		is32bitPE = checkIs32bit(peImageData);
		if (is32bitPE) {
			// set 64bit headers NULL and load 32bit headers
			NtHeader64 = NULL;
			OptHeader64 = NULL;
			readOffset += DosHeader->e_lfanew;
			NtHeader32 = (PIMAGE_NT_HEADERS32)(peImageData + readOffset);
			OptHeader32 = &NtHeader32->OptionalHeader;
		}
		else {
			// set 32bit headers NULL load 64bit headers
			NtHeader32 = NULL;
			NtHeader32 = NULL;
			readOffset += DosHeader->e_lfanew;
			NtHeader64 = (PIMAGE_NT_HEADERS64)(peImageData + readOffset);
			OptHeader64 = &NtHeader64->OptionalHeader;
		}
		FileHeader = is32bitPE ? &NtHeader32->FileHeader : &NtHeader64->FileHeader;
		for (int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++) {
			DataDirArr[i] = is32bitPE ?
				&OptHeader32->DataDirectory[i] : &OptHeader64->DataDirectory[i];
		}
		ImageBase = is32bitPE ? OptHeader32->ImageBase : OptHeader64->ImageBase;
		EntryPoint = is32bitPE ? OptHeader32->AddressOfEntryPoint : OptHeader64->AddressOfEntryPoint;

		PIMAGE_SECTION_HEADER sectionHeader = (PIMAGE_SECTION_HEADER)(
			is32bitPE ?
			(PBYTE)OptHeader32 + sizeof(IMAGE_OPTIONAL_HEADER32) :
			(PBYTE)OptHeader64 + sizeof(IMAGE_OPTIONAL_HEADER64)
			);

		sectionCount = FileHeader->NumberOfSections;
		SectionHeadersArr = (PIMAGE_SECTION_HEADER*)malloc(sizeof(PIMAGE_SECTION_HEADER*) * sectionCount);
		for (int i = 0; i < sectionCount; i++) {
			SectionHeadersArr[i] = sectionHeader + i;
		}


	} while (false);
	return peImageData;
}

PBYTE PEImage::loadPEImage(CHAR* PEPath) {
	hPEFile = CreateFileA(PEPath, GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPEFile == INVALID_HANDLE_VALUE) {
		return NULL;
	}
	return loadPEImage(hPEFile);
}

BOOL PEImage::checkIs32bit(PBYTE fileBytes) {
	PIMAGE_DOS_HEADER dosheader = (PIMAGE_DOS_HEADER)fileBytes;
	LONG offset = dosheader->e_lfanew;
	INT16 machine = *(INT16*)(fileBytes + offset + 4);

	if (machine == 0x14C) // i386
		return true;
	return false; // e.g. AMD64 0x8664
	// NOTE: not taking other machines into consideration
}

BOOL PEImage::VerifyImage(PBYTE imgData) {
	// TODO: write verification logics
	return true;
}

PEImage::PEImage() {
	is32bitPE = FALSE;
	hPEFile = INVALID_HANDLE_VALUE;
	hProc = INVALID_HANDLE_VALUE;
	sectionCount = 0;
	peImageData = NULL;
	EntryPoint = 0;
	ImageBase = 0;
	*DataDirArr = NULL;
	SectionHeadersArr = NULL;
	DosHeader = NULL;
	NtHeader32 = NULL;
	NtHeader64 = NULL;
	FileHeader = NULL;
	OptHeader32 = NULL;
	OptHeader64 = NULL;
}

PEImage::~PEImage() {
	if (peImageData != NULL) {
		free(peImageData);
		peImageData = NULL;
	}
	if (SectionHeadersArr != NULL) {
		free(SectionHeadersArr);
	}
}