#pragma once
#include "PEImage.h"
#include <qwidget.h>
#include "ui_SectionsView.h"
#include <qmenu.h>
#include <qevent.h>
#include <qclipboard.h>
#include <qpoint.h>
#include <qdebug.h>


class SectionsView : public QWidget
{
	Q_OBJECT

public:
	PEImage *peImageLocal;

	SectionsView(PEImage* peImage, QWidget* parent = Q_NULLPTR);
	~SectionsView();


private:
	Ui::SectionsViewClass ui;
	// TODO: 想想怎么把有menu功能的表格控件抽象出来
	QMenu* menu = NULL;
	QAction* action_copy;
	QTableWidgetItem* selectedItem = NULL;
	//void setup_menu();
	//void show_menu(const QPoint pos);
	void contextMenuEvent(QContextMenuEvent* event);

	void setupTableView();
	void AddItemsOneRow(int rowNo, QString name, DWORD virtualAddr, DWORD virtualSize, DWORD rawSize, int sizeDelta, DWORD characteristics);

private slots:
	void copy_item();
	void closeView();
	void click_debug();
};