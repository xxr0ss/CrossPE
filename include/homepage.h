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

private slots:
    void openFileByLineEditPath();
    void setConfirmBtnEnabled();
    void onPeImageMemoryReady(bool isReady);
    void receiveFile(QString filepath);
    void displaySectionsView();


private:
    Ui::Homepage *ui;
};

#endif // HOMEPAGE_H
