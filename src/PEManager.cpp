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
}
