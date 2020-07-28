#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CrossPE.h"
#include <qfiledialog.h>
#include <qfiledevice.h>
#include <qfile.h>
#include <qstring.h>
#include "PEImage.h"
#include "SectionsView.h"


class CrossPE : public QMainWindow
{
    Q_OBJECT

signals:
    void fileNameIsReady();

public:
    PEImage *peImage;
    QString peFileName;
    QList<QWidget> widgetsToBeEnabled;
    SectionsView* sectionsView;
    
    CrossPE(QWidget *parent = Q_NULLPTR);
    ~CrossPE();

private:
    Ui::CrossPEClass ui;

private slots:
    void dealWithArgsFile();
    void fileOpenFromMemuBar();
    void openPESectionsView();
    void peImageLoad();
};
