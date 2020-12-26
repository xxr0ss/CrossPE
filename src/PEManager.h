#ifndef PEMANAGER_H
#define PEMANAGER_H
#include <Windows.h>
#include <mutex>
#include <QtCore/qobject.h>
#include <qstring.h>


class PEManager: QObject
{
	Q_OBJECT // 反正也使用了qt的东西了，干脆做个Q_OBJECT得了，也方便使用信号和槽

public:
	static PEManager& getPEManager();

private:
	// 和实现单例模式相关的成员
	static std::mutex _mutex;
	static PEManager* _instance;
	PEManager();
	~PEManager();

private:
	BYTE* _rawPeImage = NULL;

public:
	bool isPeReady();
	void fillPe(const QString filepath);
};

#endif