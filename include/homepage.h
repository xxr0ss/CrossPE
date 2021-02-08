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

public:
    explicit Homepage(QWidget *parent = nullptr);
    ~Homepage();

private slots:
    void openFileByLineEditPath();
    void setConfirmBtnEnabled();
    void onPeImageMemoryReady();
    void openSectionsView();


private:
    Ui::Homepage *ui;
};

#endif // HOMEPAGE_H
