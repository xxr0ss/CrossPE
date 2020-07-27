#include "CrossPE.h"
#include <Windows.h>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

CrossPE::CrossPE(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void CrossPE::on_open_file_triggered() {
    QString curPath = QDir::currentPath();
    QString dlgTitle = "打开PE文件";
    QString filter = "PE文件(*.exe, *.dll);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if (aFileName.isEmpty()) {
        return;
    }
    ui.lineEditFileName->setText(aFileName);
    peFileName = aFileName;
}


void CrossPE::on_btnViewSections_clicked() {
    if (peFileName.isEmpty()) {
        MessageBox(NULL, L"No file opened!", L"Error", MB_OK);
        return;
    }
}