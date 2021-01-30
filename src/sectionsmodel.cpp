#include "sectionsmodel.h"

SectionsModel::SectionsModel()
{
	columnLabels << "Name" << "VirtualSize" << "VirtualAddress" << "SizeOfRawData"
		<< "PointerToRawData" << "PointerToRelocations" << "PointerToLinenumbers"
		<< "NumberOfRelocations" << "NumberOfLinenumbers" << "Characteristics";
}

SectionsModel::~SectionsModel()
{
	// delete &columnLabels; // donot delete, will cause failure;
}

int SectionsModel::rowCount(const QModelIndex& parent) const
{
	PEManager* manager = PEManager::getPEManager();
	return manager->getIMAGE_FILE_HEADER()->NumberOfSections;
}

int SectionsModel::columnCount(const QModelIndex& parent) const
{
	return columnLabels.length();
}

QVariant SectionsModel::data(const QModelIndex& index, int role) const
{
	// TODO: write my own logic of display sections table
	int row = index.row();
	int col = index.column();

	PEManager* manager = PEManager::getPEManager();
	auto& sectionheaders = manager->getSectionsHeaderList();
	PIMAGE_SECTION_HEADER currentSection = sectionheaders[row];
	int wordLength = manager->getWordLength(); // 根据字长，也就是32位和64位对需要区分的输出数据进行区分

	switch (role) {
	case Qt::DisplayRole:
		switch (col) {
		case 0:
			return QString((char*)currentSection->Name);
		case 1:
			return QString::asprintf("%08X", currentSection->Misc.VirtualSize);
		case 2:
			return QString::asprintf("%08X", currentSection->VirtualAddress);
		case 3:
			return QString::asprintf("%08X", currentSection->SizeOfRawData);
		case 4:
			return QString::asprintf("%08X", currentSection->PointerToRawData);
		case 5:
			return QString::asprintf("%08X", currentSection->PointerToRelocations);
		case 6:
			return QString::asprintf("%08X", currentSection->PointerToLinenumbers);
		case 7:
			return QString::asprintf("%04X", currentSection->NumberOfRelocations);
		case 8:
			return QString::asprintf("%04X", currentSection->NumberOfLinenumbers);
		case 9:
			return QString("%1").arg(currentSection->Characteristics, 32, 2, QLatin1Char('0'));
		}
		break;
	case Qt::FontRole:

		break;
	case Qt::BackgroundRole:

		break;
	case Qt::TextAlignmentRole:

		break;
	case Qt::CheckStateRole:
		break;
	}

	return QVariant();
}

QVariant SectionsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (orientation == Qt::Horizontal) {
			return columnLabels[section];
		}
		else if (orientation == Qt::Vertical) {
			return section;
		}
		break;

	case Qt::FontRole:
		QFont font;
		font.setBold(true);
		return font;
	}

	return QVariant();
}