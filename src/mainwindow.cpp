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

    connect(this, SIGNAL(externalFilepathGot(QString)), hp, SLOT(receiveFile(QString)));
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
     emit externalFilepathGot(filepath);
}

/*
 * 菜单栏的处理逻辑
*/
void MainWindow::on_actionOpen_triggered()
{
   QString filename = QFileDialog::getOpenFileName(this, "Select a file");
   qDebug() << "opened file through menu/open : " << filename;

   emit externalFilepathGot(filename);
}

void MainWindow::checkArgs()
{
    QStringList argv = QCoreApplication::arguments();
    qDebug() << argv;
    if (argv.length() > 1) {
        emit externalFilepathGot(argv[1]);
    }
}
