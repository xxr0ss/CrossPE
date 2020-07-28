#include "CrossPE.h"
#include <Windows.h>
#include <qdebug.h>
#include <qbytearray.h>
#include <qmessagebox.h>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

CrossPE::CrossPE(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    peImage = new PEImage();
    sectionsView = NULL;

    // connections
    connect(this, SIGNAL(fileNameIsReady()), this, SLOT(peImageLoad()));
    connect(ui.btnOpenSectionView, SIGNAL(clicked()), this, SLOT(openPESectionsView()));
}

CrossPE::~CrossPE() {
    // 释放镜像
    if(peImage != nullptr){
        delete peImage;
        peImage = nullptr;
    }
}

void CrossPE::dealWithArgsFile() {
    // 如果是拖动文件到exe上或者快捷方式这种，windows会把文件路径放到启动参数里
    QStringList cmdline_args = QCoreApplication::arguments();
    if (!cmdline_args.isEmpty()) {
        QString aFileName = cmdline_args[0];
        // TODO: check file validity
        ui.lineEditFileName->setText(aFileName);
    }
    emit fileNameIsReady();
}

void CrossPE::fileOpenFromMemuBar() {
    // 通过菜单打开一个文件
    QString curPath = QDir::currentPath();
    QString dlgTitle = "打开PE文件";
    QString filter = "PE文件(*.exe, *.dll);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if (aFileName.isEmpty()) {
        return;
    }
    ui.lineEditFileName->setText(aFileName);
    peFileName = aFileName;
    emit fileNameIsReady();
}



void CrossPE::peImageLoad() {
    QByteArray ba = peFileName.toLatin1();
    peImage->loadPEImage(ba.data());
}



void CrossPE::openPESectionsView() {
    if (peFileName.isEmpty()) {
        //MessageBox(NULL, L"No file opened!", L"Error", MB_OK);
        QMessageBox::information(this, "Error", "No file opened!", MB_OK);
        return;
    }

    sectionsView = new SectionsView(peImage);
    sectionsView->setAttribute(Qt::WA_DeleteOnClose);
    sectionsView->setWindowFlag(Qt::Window, true);
    sectionsView->show();
}

