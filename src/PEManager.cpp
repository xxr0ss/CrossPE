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