#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CrossPE.h"
#include <qfiledialog.h>
#include <qfiledevice.h>
#include <qfile.h>
#include <qstring.h>



class CrossPE : public QMainWindow
{
    Q_OBJECT

public:
    QString peFileName;
    CrossPE(QWidget *parent = Q_NULLPTR);

private:
    Ui::CrossPEClass ui;

private slots:
    void on_open_file_triggered();
    void on_btnViewSections_clicked();
};
