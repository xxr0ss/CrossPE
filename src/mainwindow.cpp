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
    createDockWindows();
    
    connect(this, SIGNAL(externalFilepathGot(QString)), dock_hp->widget(), SLOT(receiveFile(QString)));
    connect(dock_hp->widget(), SIGNAL(requestForSectionsView()), this, SLOT(displaySectionsView()));

    PEManager *manager = PEManager::getPEManager();
    connect(manager, SIGNAL(peImageMemoryReady(bool)), this, SLOT(onPeImageMemoryStatus(bool)));
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

void MainWindow::on_actionSections_View_triggered()
{
    qDebug() << "action: Sections_View triggered";
    displaySectionsView();
}

void MainWindow::onPeImageMemoryStatus(bool isReady)
{
    ui->menuPE->setEnabled(isReady);
    ui->actionSections_View->setEnabled(isReady);
}

void MainWindow::displaySectionsView()
{
    qDebug() << "to display sections view";
    if (dock_sv == nullptr) {
        SectionsView* sv = new SectionsView();
        dock_sv = new QDockWidget("Sections View", this);
        dock_sv->setAllowedAreas(Qt::AllDockWidgetAreas);
        dock_sv->setWidget(sv);
    }

    if (dock_hp->isVisible()) {
        qDebug() << "dock_hp visible, will tabify docks";
        dock_sv->setVisible(true);
        tabifyDockWidget(dock_hp, dock_sv);
    }
    else {
        addDockWidget(Qt::TopDockWidgetArea, dock_sv);
    }
}


void MainWindow::checkArgs()
{
    QStringList argv = QCoreApplication::arguments();
    qDebug() << argv;
    if (argv.length() > 1) {
        emit externalFilepathGot(argv[1]);
    }
}

void MainWindow::createDockWindows()
{
    if (dock_hp == nullptr) {
        dock_hp = new QDockWidget("Homepage", this);
        dock_hp->setAllowedAreas(Qt::AllDockWidgetAreas);
        Homepage *hp = new Homepage(this);
        dock_hp->setWidget(hp);
        addDockWidget(Qt::TopDockWidgetArea, dock_hp);
        ui->menuPE->addAction(dock_hp->toggleViewAction());
    }
    else {
        addDockWidget(Qt::TopDockWidgetArea, dock_hp);
    }
}
