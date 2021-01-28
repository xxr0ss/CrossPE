#include "sectionsview.h"
#include "ui_sectionsview.h"

SectionsView::SectionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SectionsView)
{
    ui->setupUi(this);
    setupSectionsTable();
}

SectionsView::~SectionsView()
{
    delete ui;
}

void SectionsView::setupSectionsTable()
{

    ui->sectionsTableView->setModel(new SectionsModel);
    
}


