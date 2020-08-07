#include "ImportView.h"

ImportView::ImportView(PEImage* peimage) {
	image = peimage;
	ui.setupUi(this);

	this->setLayout(ui.verticalLayout);

	iidImport = image->iidImport;
	currentDllRow = 0;
	setupImportTable();

	// 点击dll列表的时候，更新dll的import descriptor，也就是更新INT
	connect(ui.dllsTable, SIGNAL(itemClicked(QTableWidgetItem * item)),
		ui.impDespTable, SLOT(updataImpDespTable(QTableWidgetItem * item)));
}

ImportView::~ImportView() {

}

void ImportView::setupImportTable() {
	QTableWidget* table = ui.dllsTable;

	// 设置行列数量
	int dllsCnt = image->getImportNum();
	table->setRowCount(dllsCnt);
	table->setColumnCount(6);

	// 设置要展示的项
	QStringList headerText;
	headerText << "Dll Name" << "OriginalFirstThunk" << "TimeDataStamp"
			   << "ForwardChain" << "Name" << "FirstThunk";
	table->setHorizontalHeaderLabels(headerText);

	QString tmp;
	PIMAGE_IMPORT_DESCRIPTOR iid = (PIMAGE_IMPORT_DESCRIPTOR)
		image->getPtrInBufferByVA(iidImport->VirtualAddress);
	for (int row = 0; row < dllsCnt; row++, iid++) {
		int col = 0;
		// Dll Name:
		tmp = (char*)(image->getPtrInBufferByVA(iid->Name));
		table->setItem(row, col++, new QTableWidgetItem(tmp));

		// Other:
		tmp.sprintf("%08X", iid->OriginalFirstThunk);
		table->setItem(row, col++, new QTableWidgetItem(tmp));
		tmp.sprintf("%08X", iid->TimeDateStamp);
		table->setItem(row, col++, new QTableWidgetItem(tmp));
		tmp.sprintf("%08X", iid->ForwarderChain);
		table->setItem(row, col++, new QTableWidgetItem(tmp));
		tmp.sprintf("%08X", iid->Name);
		table->setItem(row, col++, new QTableWidgetItem(tmp));
		tmp.sprintf("%08X", iid->FirstThunk);
		table->setItem(row, col++, new QTableWidgetItem(tmp));
	}

}

void ImportView::updataImpDespTable(QTableWidgetItem* item) {
	//int clicked_row = item->row();
	//// 和之前是同一行的dll)
	//if(clicked_row == currentDllRow)
	//	return;

	//// 构造要填充的数据

	//int thunkNum = ;

	//// 填充表格
	//for (int row = 0; row < thunkNum; row++) {
	//	fillOneRowWithQList(ui.impDespTable, row, )
	//}
}
