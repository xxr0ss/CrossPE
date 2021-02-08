#include "mainwindow.h"
#include "./ui_mainwindow.h"


/*
* Constructr(s) and destructor
*/

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setAcceptDrops(true);
    Homepage *hp = new Homepage();
    setCentralWidget(hp);
}

MainWindow::~MainWindow()
{
	delete ui;
}




/*
* Handle file drag and drop
*/

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasFormat("text/uri-list")) {
		event->acceptProposedAction();
	}
}

void MainWindow::dropEvent(QDropEvent* event)
{
	// QList<QUrl> urls = event->mimeData()->urls();
	// if (urls.isEmpty())
	// 	return;
	// if (urls.count() > 1) {
	// 	QMessageBox::information(this, "Invalid Operation", "One file at a time!", QMessageBox::Ok);
	// 	return;
	// }

	// QUrl url = urls.first();
	// QString filepath = url.toLocalFile();   // 去掉url前面的"file://"
	// QLineEdit* le = ui->FilePathEdit;
	// qDebug() << filepath;

	// le->setText(filepath);
	// //ui->FilePathEdit->setDisabled(true);    // 设置禁止再编辑

	// emit(le->editingFinished());    // 避免还需要按回车才能启用确定按钮
}



/*
* 文件处理
*/

/* 文件路径得到之后都设置下主界面的路径编辑框，再通过这个把文件打开，对PEManager进行数据填充*/
//void MainWindow::openFileByLineEditPath() {
//	 qDebug() << "clicked confirm button";

//	 QString filepath = ui->FilePathEdit->text();
//	 qDebug() << "File path: " << filepath;

//	 PEManager* pemanager = PEManager::getPEManager();
//	 pemanager->fillPe(filepath);
//}



/*
* Slots of MainWindow class
*/

//void MainWindow::setConfirmBtnEnabled()
//{
//	// ui->ConfirmFileBtn->setEnabled(true);
//}


/*
 * 菜单栏的处理逻辑
*/
// TODO: fix these
void MainWindow::on_actionOpen_triggered()
{
   QString filename = QFileDialog::getOpenFileName(this, "Select a file");
   qDebug() << "opened file through menu/open : " << filename;

   // ui->FilePathEdit->setText(filename);
   // emit(ui->FilePathEdit->editingFinished());
}
