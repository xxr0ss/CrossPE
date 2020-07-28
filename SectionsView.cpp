#include "SectionsView.h"
#include <qtablewidget.h>

SectionsView::SectionsView(PEImage* peImage, QWidget* parent) {
	peImageLocal = peImage;
	ui.setupUi(this);
	setupTableView();
	// SectionsTable是tableVertLayout的child，所以这样可以使得table填充满整个窗口
	this->setLayout(ui.tableVertLayout);
	ui.SectionsTable->horizontalHeader()->setStretchLastSection(true);
	ui.SectionsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

SectionsView::~SectionsView() {

}

void SectionsView::setupTableView() {
	QTableWidget* table = ui.SectionsTable;

	QTableWidgetItem* headerItem;
	QStringList headerText;
	headerText << "Name" << "V.Address" << "V.Size" << "V.RawSize" << "V.R.DeltaSize" << "Characteristics";
	int count = headerText.count();
	table->setColumnCount(count);
	for (int i = 0; i < table->columnCount(); i++) {
		headerItem = new QTableWidgetItem(headerText.at(i));
		QFont font = headerItem->font();
		font.setBold(true);
		font.setPointSize(9);
		headerItem->setFont(font);
		table->setHorizontalHeaderItem(i, headerItem);
	}


	DWORD numSections = peImageLocal->sectionCount;
	char namebuffer[9] = { 0 };
	table->setRowCount(numSections);
	for (int i = 0; i < numSections; i++) {
		PIMAGE_SECTION_HEADER secHeader = peImageLocal->SectionHeadersArr[i];
		memset(namebuffer, 0, 8);
		memcpy(namebuffer, (char*)secHeader->Name, 8);
		QString name(namebuffer);
		DWORD virtualAddr = secHeader->VirtualAddress;
		DWORD virtualSize = secHeader->Misc.VirtualSize;
		DWORD rawSize = secHeader->Misc.PhysicalAddress;
		int sizeDelta = virtualAddr - rawSize;
		DWORD characteristics = secHeader->Characteristics;
		AddItemsOneRow(i, name, virtualAddr, virtualSize, rawSize, sizeDelta, characteristics);
	}


}

void SectionsView::AddItemsOneRow(int rowNo, QString name, DWORD virtualAddr, DWORD virtualSize, DWORD rawSize, int sizeDelta, DWORD characteristics) {
	QTableWidget* table = ui.SectionsTable;

	int col = 0;
	table->setItem(rowNo, col++, new QTableWidgetItem(name));
	QString tmp;
	tmp = tmp.sprintf("%08X", virtualAddr);
	table->setItem(rowNo, col++, new QTableWidgetItem(tmp));
	table->setItem(rowNo, col++, new QTableWidgetItem(tmp.sprintf("%08X", virtualSize)));
	table->setItem(rowNo, col++, new QTableWidgetItem(tmp.sprintf("%08X", rawSize)));
	table->setItem(rowNo, col++, new QTableWidgetItem(tmp.sprintf("%8X", sizeDelta)));
	QString chs = QString::number(characteristics, 2);
	int zeroNeeded = 32 - chs.count();
	char zeros[32] = { 0 };
	memset(zeros, '0', zeroNeeded);
	chs = QString(zeros) + chs;
	table->setItem(rowNo, col++, new QTableWidgetItem(chs));
}

void SectionsView::closeView() {
	close();
}