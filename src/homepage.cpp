#include "homepage.h"
#include "./ui_homepage.h"

Homepage::Homepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Homepage)
{
    ui->setupUi(this);
    connect(ui->FilePathEdit, SIGNAL(editingFinished()), this, SLOT(setConfirmBtnEnabled())); // 手动输入完后，确认按钮能正确启用
    PEManager* pemanager = PEManager::getPEManager();
    connect(pemanager, SIGNAL(peImageMemoryReady()), this, SLOT(onPeImageMemoryReady()));
    
    QStringList argv = QCoreApplication::arguments();
	qDebug() << argv;
	if (argv.length() > 1) {
		ui->FilePathEdit->setText(argv[1]);
		ui->FilePathEdit->editingFinished();
	}
}

Homepage::~Homepage()
{
    delete ui;
}


/*
* 文件处理
*/

/* 文件路径得到之后都设置下主界面的路径编辑框，再通过这个把文件打开，对PEManager进行数据填充*/
void Homepage::openFileByLineEditPath() {
	qDebug() << "clicked confirm button";

	QString filepath = ui->FilePathEdit->text();
	qDebug() << "File path: " << filepath;

	PEManager* pemanager = PEManager::getPEManager();
	pemanager->fillPe(filepath);
}

/*
* Slots
*/

void Homepage::setConfirmBtnEnabled()
{
	ui->ConfirmFileBtn->setEnabled(true);
}

void Homepage::onPeImageMemoryReady()
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
	
	// display file size
	ui->FileSizeLE->setEnabled(true);
	ui->FileSizeLE->setText(size);

	// display architecture info
	ui->ArchLE->setEnabled(true);
	ui->ArchLE->setText(manager->getMachineTypeName());

	// display pe type (exe, dll, sys etc.)
	ui->PEtypeLE->setEnabled(true);
	ui->PEtypeLE->setText(manager->getPETypeName());

    // enable sections view button
    ui->sectionsView_bt->setEnabled(true);

	// test getFo_IMAGE_OPTION_HEADER
//	DWORD opt_header_address = manager->getFo_IMAGE_OPTIONAL_HEADER();
}


void Homepage::openSectionsView()
{
//    SectionsView *sv = new SectionsView();
//    sv->setAttribute(Qt::WA_DeleteOnClose);
//    sv->setWindowFlag(Qt::Window, true);
//    sv->show();
}
