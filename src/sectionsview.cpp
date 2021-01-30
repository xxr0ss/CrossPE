#include "sectionsview.h"
#include "ui_sectionsview.h"

#include <qstandarditemmodel.h>

SectionsView::SectionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SectionsView)
{
    ui->setupUi(this);
    model = new SectionsModel();;
    ui->sectionsTableView->setModel(model);
}

SectionsView::~SectionsView()
{
    delete ui;
    delete model;
}