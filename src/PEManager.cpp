#include "PEManager.h"

/*
* 静态变量进行初始化
*/
PEManager* PEManager::_instance = nullptr;
std::mutex PEManager::_mutex;

PEManager::PEManager()
{
}

PEManager::~PEManager()
{
}


PEManager& PEManager::getPEManager()
{
	if (_instance == nullptr) {
		_mutex.lock();
		if (_instance == nullptr) {
			_instance = new PEManager();
		}
		_mutex.unlock();
	}

	return *_instance;
}

bool PEManager::isPeReady() { return _rawPeImage != NULL; }

void PEManager::fillPe(const QString filepath)
{
}
