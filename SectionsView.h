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

private:
	void setupTableView();
	void AddItemsOneRow(int rowNo, QString name, int virtualAddr, int virtualSize, int rawSize, int sizeDelta, int characteristics);
};