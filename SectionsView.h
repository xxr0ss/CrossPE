#pragma once
#include "PEImage.h"
#include <qwidget.h>
#include "ui_SectionsView.h"


class SectionsView : public QWidget
{
	Q_OBJECT

public:
	PEImage *peImageLocal;

	SectionsView(PEImage* peImage, QWidget* parent = Q_NULLPTR);
	~SectionsView();


private:
	Ui::SectionsViewClass ui;

	void setupTableView();
	void AddItemsOneRow(int rowNo, QString name, DWORD virtualAddr, DWORD virtualSize, DWORD rawSize, int sizeDelta, DWORD characteristics);

private slots:
	void closeView();
};