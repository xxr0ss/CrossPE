#include "SectionsView.h"
#include <qtablewidget.h>

SectionsView::SectionsView(PEImage* peImage, QWidget* parent) {
	peImageLocal = peImage;
	ui.setupUi(this);
	setupTableView();

	// setup right click menu
	menu = new QMenu(ui.SectionsTable);
	action_copy = new QAction("Copy", ui.SectionsTable);
	connect(action_copy, SIGNAL(triggered()), this, SLOT(copy_item()));
	//connect(ui.SectionsTable, SIGNAL(itemClicked(QTableWidgetItem)), this, SLOT(click_debug()));
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

	DWORD numSections = peImageLocal->sectionCount;
	table->setRowCount(numSections);

	table->setHorizontalHeaderLabels(headerText);
	char namebuffer[9] = { 0 };
	for (int i = 0; i < numSections; i++) {
		PIMAGE_SECTION_HEADER secHeader = peImageLocal->SectionHeadersArr[i];
		memset(namebuffer, 0, 8);
		memcpy(namebuffer, (char*)secHeader->Name, 8);
		QString name(namebuffer);
		DWORD virtualAddr = secHeader->VirtualAddress;
		DWORD virtualSize = secHeader->Misc.VirtualSize;
		DWORD rawSize = secHeader->SizeOfRawData;
		int sizeDelta = virtualAddr - rawSize;
		DWORD characteristics = secHeader->Characteristics;
		AddItemsOneRow(i, name, virtualAddr, virtualSize, rawSize, sizeDelta, characteristics);
	}
	// Debug
	qDebug() << ui.SectionsTable->item(0, 0)->text();
}

//void SectionsView::show_menu(const QPoint pos) {
//	
//}
void SectionsView::contextMenuEvent(QContextMenuEvent* event) {
	menu->clear();
	qDebug() << ui.SectionsTable->columnWidth(0);
	QPoint point = event->pos();
	qDebug() << '(' << point.x() << ',' << point.y() << ')';
	if (!ui.SectionsTable->underMouse() || point.x() <= 25) {
		// 25是左边行标的宽度，还没找到获取第0列的起始x坐标的方法，所以用这个先代替了。
		event->ignore();
		return;
	}
	selectedItem = ui.SectionsTable->currentItem(); // 设置选中的selectedItem
	qDebug() << point.x() << point.y();
	qDebug() << "row" << selectedItem->row() << ' ' << "col" << selectedItem->column() << selectedItem << selectedItem->text();
	if (selectedItem == NULL) {
		event->ignore();
		return;
	}
	menu->addAction(action_copy);
	menu->exec(QCursor::pos());
	event->accept();
}

void SectionsView::click_debug() {
	qDebug() << ui.SectionsTable->currentItem();
}

void SectionsView::copy_item() {
	qDebug() << selectedItem;
	QString content = selectedItem->text(); // 从选中的item获得字符串
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(content);
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