#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include "./PEManager.h"
#include "sectionsview.h"

#include <QWidget>

namespace Ui {
class Homepage;
}

class Homepage : public QWidget
{
    Q_OBJECT
signals:
    void requestForSectionsView();

public:
    explicit Homepage(QWidget *parent = nullptr);
    ~Homepage();
    QSize sizeHint() const; // 用于父窗口能以正确大小显示该控件dock

private slots:
    void openFileByLineEditPath();
    void setConfirmBtnEnabled();
    void onPeImageMemoryReady(bool isReady);
    void receiveFile(QString filepath);
    void displaySectionsView();


private:
    Ui::Homepage *ui;
    QWidget* parent;
};

#endif // HOMEPAGE_H
