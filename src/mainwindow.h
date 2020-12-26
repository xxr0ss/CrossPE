#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PEManager.h"

#include <QMainWindow>
#include <qdrag.h>
#include <qevent.h>
#include <qpoint.h>
#include <qrect.h>
#include <qfile.h>
#include <qiodevice.h>
#include <qmimedata.h>
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qdebug.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void lineEditFilePathReady();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

private slots:
    void openFileByLineEditPath();
    void setConfirmBtnEnabled();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


