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

		if (!VerifyImage(peImageData)) {
			peImageData = NULL;
			break;
		}

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
	do {
		// 校验"MZ"头
		if (*(PWORD)imgData != 0x5A4D)
			return FALSE;

		// 校验"PE"头
		PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)imgData;
		if (*(PWORD)(imgData + dos_header->e_lfanew) != 0x4550)
			return FALSE;

	} while (FALSE);
	return TRUE;
}

PIMAGE_SECTION_HEADER PEImage::LocationSectionByRVA(int VirtualAddr) {
	PIMAGE_SECTION_HEADER tmpSec = SectionHeadersArr[0];
	for (int i = 0; i < sectionCount; i++) {
		if (tmpSec->VirtualAddress <= VirtualAddr &&
			VirtualAddr < (tmpSec->VirtualAddress + tmpSec->Misc.VirtualSize))
		{
			return tmpSec;
		}
		tmpSec++;
	}
	return NULL;
}


int PEImage::getImportNum() {
	// 根据导入表项来计算的，所以如果修改了的话，获得的总是新的值，还会更新iidImportCnt
	int size = iidImport->Size;
	iidImportCnt = (size / 0x14) - 1;
	return iidImportCnt;
}

DWORD PEImage::Rva2Raw(DWORD va) {
	DWORD raw = 0;
	int sizeOfHeaders = is32bitPE ? OptHeader32->SizeOfHeaders : OptHeader64->SizeOfHeaders;
	if (va < sizeOfHeaders) {
		raw = va;
	}
	PIMAGE_SECTION_HEADER tmpSecHeader = LocationSectionByRVA(va);
	if (tmpSecHeader != NULL) {
		raw = va - tmpSecHeader->VirtualAddress + tmpSecHeader->PointerToRawData;
	}
	return raw;
}

PBYTE PEImage::getPtrInBufferByVA(int VirtualAddr) {
	int raw = Rva2Raw(VirtualAddr);
	if (raw > fileSize) {
		return NULL;
	}
	return (PBYTE)(peImageData + raw);
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

	iidImportCnt = 0;
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