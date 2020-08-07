#pragma once
#include "ui_ImportView.h"
#include "qtablewidget.h"
#include "PEImage.h"
#include <qlist.h>
#include <qstring.h>
#include <qstringlist.h>

class ImportView : public QWidget
{
	Q_OBJECT
public:
	PEImage* image;
	PIMAGE_DATA_DIRECTORY iidImport;
	int currentDllRow;

	ImportView(PEImage* peimage);
	~ImportView();
private:
	Ui::ImportViewClass ui;

	void setupImportTable();
	void loadDllsTable();
	void loadImpDespTable();

	void fillOneRowWithQList(QTableWidgetItem* targetTable, 
		int row, QStringList itemsData);

private slots:
	void updataImpDespTable(QTableWidgetItem* item);
};