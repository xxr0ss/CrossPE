#ifndef SECTIONSVIEW_H
#define SECTIONSVIEW_H

#include <QWidget>

namespace Ui {
class SectionsView;
}

class SectionsView : public QWidget
{
    Q_OBJECT

public:
    explicit SectionsView(QWidget *parent = nullptr);
    ~SectionsView();

private:
    Ui::SectionsView *ui;
};

#endif // SECTIONSVIEW_H
