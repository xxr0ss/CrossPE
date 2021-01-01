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

	connect(ui->FilePathEdit, SIGNAL(editingFinished()), this, SLOT(setConfirmBtnEnabled())); // 手动输入完后，确认按钮能正确启用

	PEManager* pemanager = PEManager::getPEManager();
	connect(pemanager, SIGNAL(peImageMemoryReady()), this, SLOT(onPeImageMemoryReady()));
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
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;
	if (urls.count() > 1) {
		QMessageBox::information(this, "Invalid Operation", "One file at a time!", QMessageBox::Ok);
		return;
	}

	QUrl url = urls.first();
	QString filepath = url.toLocalFile();   // 去掉url前面的"file://"
	QLineEdit* le = ui->FilePathEdit;
	qDebug() << filepath;

	le->setText(filepath);
	//ui->FilePathEdit->setDisabled(true);    // 设置禁止再编辑

	emit(le->editingFinished());    // 避免还需要按回车才能启用确定按钮
}



/*
* 文件处理
*/

void MainWindow::openFileByLineEditPath() {
	qDebug() << "clicked confirm button";

	QString filepath = ui->FilePathEdit->text();
	qDebug() << "File path: " << filepath;

	PEManager* pemanager = PEManager::getPEManager();
	pemanager->fillPe(filepath);
}



/*
* Slots of MainWindow class
*/

void MainWindow::setConfirmBtnEnabled()
{
	ui->ConfirmFileBtn->setEnabled(true);
}


void MainWindow::onPeImageMemoryReady()
{
	qDebug() << "peImageMemory ready, can now start analysing";
	PEManager *manager = PEManager::getPEManager();

	// display file info
	int file_size = manager->getPeImageSize();
	QString size;
	if (file_size < 1024) {
		size = QString::asprintf("%d B", file_size);
	}
	else if (file_size < 1024 * 1024) {
		size = QString::asprintf("%d KB (%d bytes)", file_size >> 10, file_size);
	}
	else if (file_size < 1024 * 1024 * 1024) {
		int kb = file_size % (1 << 20);
		size = QString::asprintf("%.2f MB (%d bytes)", 
			(file_size >> 20) + (double)kb / (double)(1 << 20), file_size);
	}
	else {
		// TODO 实现精度更高的显示
		size = QString::asprintf("%d GB", file_size >> 30);
	}
	
	ui->FileSizeLE->setEnabled(true);
	ui->FileSizeLE->setText(size);

	// TODO read architecture
	ui->ArchLE->setEnabled(true);
	ui->ArchLE->setText(manager->getMachineTypeName());
}