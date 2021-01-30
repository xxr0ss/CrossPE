#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PEManager.h"
#include "sectionsview.h"

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
#include <qfiledialog.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void lineEditFilePathReady(); // TODO: 这个并没有被用到

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

private slots:
    void openFileByLineEditPath();
    void setConfirmBtnEnabled();
    void onPeImageMemoryReady();

    void on_actionOpen_triggered();

    void openSectionsView();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


