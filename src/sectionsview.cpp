#include "sectionsview.h"
#include "ui_sectionsview.h"

SectionsView::SectionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SectionsView)
{
    ui->setupUi(this);
}

SectionsView::~SectionsView()
{
    delete ui;
}
