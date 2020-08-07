#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CrossPE.h"
#include <qfiledialog.h>
#include <qfiledevice.h>
#include <qfile.h>
#include <qstring.h>
#include "PEImage.h"
#include "SectionsView.h"
#include "ImportView.h"
#include <qdrag.h>
#include <qevent.h>
#include <qmimedata.h>


class CrossPE : public QMainWindow
{
    Q_OBJECT

signals:
    void fileNameIsReady();
    void imageLoaded();

public:
    PEImage *peImage;
    QString peFileName;
    QList<QWidget> widgetsToBeEnabled;
    SectionsView* sectionsView;
    ImportView* importView;

    
    CrossPE(QWidget *parent = Q_NULLPTR);
    ~CrossPE();

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

private:
    Ui::CrossPEClass ui;

private slots:
    void dealWithArgsFile();
    void fileOpenWithDialog();
    void openPESectionsView();
    void openImportTableView();
    void peImageLoad();
    void afterImageLoaded();
};
