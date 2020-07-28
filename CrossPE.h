#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CrossPE.h"
#include <qfiledialog.h>
#include <qfiledevice.h>
#include <qfile.h>
#include <qstring.h>
#include "PEImage.h"


class CrossPE : public QMainWindow
{
    Q_OBJECT

signals:
    void fileNameIsReady();

public:
    PEImage *peImage;
    QString peFileName;
    QList<QWidget> widgetsToBeEnabled;
    
    CrossPE(QWidget *parent = Q_NULLPTR);
    ~CrossPE();
    void openPESectionsView();

private:
    Ui::CrossPEClass ui;

private slots:
    void dealWithArgsFile();
    void fileOpenFromMemuBar();
    void peImageLoad();
};
