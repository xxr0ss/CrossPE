#include "CrossPE.h"
#include <Windows.h>
#include <qdebug.h>


#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

CrossPE::CrossPE(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    peImage = new PEImage();

    // connections
    connect(this, SIGNAL(fileNameIsReady()), this, SLOT(peImageLoad()));
}

CrossPE::~CrossPE() {
    // 释放镜像
    if(peImage != nullptr){
        delete peImage;
        peImage = nullptr;
    }
}

void CrossPE::dealWithArgsFile() {
    QStringList cmdline_args = QCoreApplication::arguments();
    if (!cmdline_args.isEmpty()) {
        QString aFileName = cmdline_args[0];
        // TODO: check file validity
        ui.lineEditFileName->setText(aFileName);
    }
    emit fileNameIsReady();
}

void CrossPE::fileOpenFromMemuBar() {
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
    // peImage->loadimage();
    int a = 100;
}



void CrossPE::openPESectionsView() {
    if (peFileName.isEmpty()) {
        MessageBox(NULL, L"No file opened!", L"Error", MB_OK);
        return;
    }
}

