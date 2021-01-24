#include "PEManager.h"

/*
* 静态变量进行初始化
*/

PEManager* PEManager::_instance = nullptr;
std::mutex PEManager::_mutex;

PEManager* PEManager::getPEManager()
{
	if (!_instance) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (!_instance) {
			_instance = new PEManager();
			return _instance;
		}
	}
	return _instance;
}

PEManager::PEManager()
{
}

PEManager::~PEManager()
{
}


bool PEManager::isPeReady() { return _rawPeImage != NULL; }

void PEManager::fillPe(const QString filepath)
{
	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(NULL, "File Error", "Cannot open file", QMessageBox::Ok);
		return;
	}

	QByteArray bytes = file.read(2);
	char MZ[2] = { 'M', 'Z' };
	if (!bytes.startsWith(MZ)) {
		QMessageBox::StandardButton button = QMessageBox::question(NULL,
			"Might not PE", "Not begin with \"MZ\", continue?",
			QMessageBox::Yes | QMessageBox::Cancel);
		if (QMessageBox::Cancel == button) {
			qDebug() << "Clicked Cancel button, Will cancel reading bytes into memory";
			return;
		}
	}
	// now it's QMessageBox::Yes

	QByteArray restBytes = file.readAll();
	bytes.append(restBytes);
	fillRawPeImage(bytes);
}

/*
* 将PEManager管理的PE文件buffer进行填充
*/
void PEManager::fillRawPeImage(QByteArray bytesArr) {
	peImageSize = bytesArr.size();
	if (_rawPeImage != NULL) {
		// 考虑到之前还可能有打开过别的PE文件，所以这里有必要清理内存
		free(_rawPeImage);
	}
	_rawPeImage = (BYTE*)malloc(sizeof(BYTE) * bytesArr.size());
	if (_rawPeImage == NULL) {
		QMessageBox::critical(NULL,
			"Fatal Error", "Cannot read pe file into memory: allocate memory failed",
			QMessageBox::Ok);
		return;
	}

	memcpy(_rawPeImage, bytesArr.constData(), bytesArr.size());
	qDebug() << "emit peImageMemory";
	emit peImageMemoryReady();
}

int PEManager::getPeImageSize()
{
	qDebug() << "peImageSize" << peImageSize;
	return peImageSize;
}


/*
* 获取并更新PEManager中机器类型
*
* 本质上是通过FileHeader.Machine
*/
WORD PEManager::getMachineType()
{
	DWORD file_header_addr = getFo_IMAGE_FILE_HEADER();
	qDebug() << ((PIMAGE_FILE_HEADER)(_rawPeImage + file_header_addr))->Machine;
	peMachineType = ((PIMAGE_FILE_HEADER)(_rawPeImage + file_header_addr))->Machine;
	return peMachineType;
}

QString PEManager::getMachineTypeName() {
	getMachineType();
	switch (peMachineType) {
	case IMAGE_FILE_MACHINE_UNKNOWN:
		return QString("Unknown");
	case IMAGE_FILE_MACHINE_I386:
		return QString("X86");
	case IMAGE_FILE_MACHINE_AMD64:
		return QString("AMD64");
	default:
		return QString("Unsupported");
	}
}


QString PEManager::getPETypeName() {
	// 获取PE文件类型
	PIMAGE_FILE_HEADER file_header = (PIMAGE_FILE_HEADER)(getFo_IMAGE_FILE_HEADER() + _rawPeImage);
	WORD chars = file_header->Characteristics;
	if (IMAGE_FILE_EXECUTABLE_IMAGE | chars) {
		return QString("Executable");
	}

	if (IMAGE_FILE_DLL | chars) {
		return QString("Dynamic link library");
	}

	if (IMAGE_FILE_SYSTEM | chars) {
		return QString("System file");
	}

	return QString("Unknown file type");
}


int PEManager::getWordLength()
{
	PIMAGE_OPTIONAL_HEADER h = (PIMAGE_OPTIONAL_HEADER)(_rawPeImage + getFo_IMAGE_OPTIONAL_HEADER());
	if (h->Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
		return 32;
	}
	else if (h->Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
		return 64;
	}
	return -1;
}



/*
* 各种用于获取文件偏移的函数
*/

DWORD PEManager::getFo_IMAGE_NT_HEADERS()
{
	return ((PIMAGE_DOS_HEADER)_rawPeImage)->e_lfanew;
}

DWORD PEManager::getFo_IMAGE_FILE_HEADER()
{
	DWORD fo_nt_headers = getFo_IMAGE_NT_HEADERS();
	return (DWORD) & (((PIMAGE_NT_HEADERS)fo_nt_headers)->FileHeader); // FIXEME 感觉有点问题
	//return fo_nt_headers + sizeof(DWORD);
}

DWORD PEManager::getFo_IMAGE_OPTIONAL_HEADER()
{
	DWORD fo_nt_headers = getFo_IMAGE_NT_HEADERS();
	return (DWORD)&(((PIMAGE_NT_HEADERS)fo_nt_headers)->OptionalHeader);
}
