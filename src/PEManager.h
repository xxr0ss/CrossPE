#ifndef PEMANAGER_H
#define PEMANAGER_H
#include <Windows.h>
#include <mutex>
#include <qobject.h>
#include <qstring.h>
#include <qfile.h>
#include <qiodevice.h>
#include <qmessagebox.h>
#include <qbytearray.h>
#include <qdebug.h>


class PEManager: public QObject
{
	Q_OBJECT // 反正也使用了qt的东西了，干脆做个Q_OBJECT得了，也方便使用信号和槽

signals:
	void peImageMemoryReady(); // _rawPeImage被填充完毕

public:
	static PEManager* getPEManager();
	PEManager();
	~PEManager();

private:
	static std::mutex _mutex;
	static PEManager* _instance;

private:
	BYTE* _rawPeImage = NULL;
	int peImageSize = 0;
	void fillRawPeImage(QByteArray bytesArr);

	WORD peMachineType = IMAGE_FILE_MACHINE_UNKNOWN; // IMAGE_FILE_HEADER.Machine

public:
	bool isPeReady();
	void fillPe(const QString filepath);

	int getPeImageSize();
	WORD getMachineType();
	QString getMachineTypeName();
	QString getPETypeName();
	int getWordLength(); // 快速区分是32位还是64位


public:
	/*
	* 这里定义用于获取对于读入的这个PE文件而言，常用PE文件结构的fileOffset： fo
	*/

	// TODO add boundary check

	// TODO have these functions tested

	/* 获取dos头文件偏移 */
	DWORD getFo_IMAGE_DOS_HEADER() {
		return 0;
	}

	/* 获取NT头文件偏移*/
	DWORD getFo_IMAGE_NT_HEADERS();

	/* 获取IMAGE_FILE头文件偏移*/
	DWORD getFo_IMAGE_FILE_HEADER();

	/* 获取可选头文件偏移，不区分32和64位*/
	DWORD getFo_IMAGE_OPTIONAL_HEADER();

	/* 获取节区头数组文件偏移*/
	DWORD getFo_IMAGE_SECTION_HEADER_arr();


public:
	/*
	* 这里定义用于快速获取_rawPeImage常用PE文件结构体的地址的函数
	*
	* 这里的函数大都依赖上面那些用于获取文件偏移的函数实现，上面要补充的时候，不推荐使用这里的函数来实现，
	* 相互依赖的话，维护会比较麻烦易错。
	*
	* makesure _rawPeImage is ready before calling these functions
	*/

	PIMAGE_DOS_HEADER getIMAGE_DOS_HEADER() {
		return (PIMAGE_DOS_HEADER)_rawPeImage;
	}

	PIMAGE_FILE_HEADER getIMAGE_FILE_HEADER() {

	}

	/* 用于获取节区头数组中，第i个节区头*/
	PIMAGE_SECTION_HEADER getIMAGE_SECTION_HEADER(int idx);
};

#endif
