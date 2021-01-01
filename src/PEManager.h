#ifndef PEMANAGER_H
#define PEMANAGER_H
#include <Windows.h>
#include <mutex>
#include <QtCore/qobject.h>
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
	void analysisPE();
};

#endif
