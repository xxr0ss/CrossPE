#include "SectionsView.h"
#include <qtablewidget.h>

SectionsView::SectionsView(PEImage* peImage, QWidget* parent) {
	peImageLocal = peImage;
	ui.setupUi(this);
	setupTableView();
	// SectionsTable是tableVertLayout的child，所以这样可以使得table填充满整个窗口
	this->setLayout(ui.tableVertLayout);
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
	table->setRowCount(numSections);
	for (int i = 0; i < numSections; i++) {
		PIMAGE_SECTION_HEADER secHeader = peImageLocal->SectionHeadersArr[i];
		QString name((char*)secHeader->Name);
		int virtualAddr = secHeader->VirtualAddress;
		int virtualSize = secHeader->Misc.VirtualSize;
		int rawSize = secHeader->Misc.PhysicalAddress;
		int sizeDelta = virtualAddr - rawSize;
		int characteristics = secHeader->Characteristics;
		AddItemsOneRow(i, name, virtualAddr, virtualSize, rawSize, sizeDelta, characteristics);
	}


}

void SectionsView::AddItemsOneRow(int rowNo, QString name, int virtualAddr, int virtualSize, int rawSize, int sizeDelta, int characteristics) {
	QTableWidget* table = ui.SectionsTable;

	int col = 0;
	table->setItem(rowNo, col++, new QTableWidgetItem(name));
	QString tmp;
	tmp = tmp.sprintf("%08X", virtualAddr);
	table->setItem(rowNo, col++, new QTableWidgetItem(tmp));
	table->setItem(rowNo, col++, new QTableWidgetItem(QString::number(virtualSize, 16)));
	table->setItem(rowNo, col++, new QTableWidgetItem(QString::number(rawSize, 16)));
	table->setItem(rowNo, col++, new QTableWidgetItem(QString::number(sizeDelta, 16)));
	table->setItem(rowNo, col++, new QTableWidgetItem(QString::number(characteristics, 2)));
}