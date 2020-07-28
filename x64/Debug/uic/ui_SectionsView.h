/********************************************************************************
** Form generated from reading UI file 'SectionsView.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECTIONSVIEW_H
#define UI_SECTIONSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SectionsViewClass
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *tableVertLayout;
    QTableWidget *SectionsTable;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SectionsViewClass)
    {
        if (SectionsViewClass->objectName().isEmpty())
            SectionsViewClass->setObjectName(QString::fromUtf8("SectionsViewClass"));
        SectionsViewClass->resize(910, 300);
        SectionsViewClass->setMinimumSize(QSize(0, 120));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        SectionsViewClass->setFont(font);
        verticalLayoutWidget = new QWidget(SectionsViewClass);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 791, 281));
        tableVertLayout = new QVBoxLayout(verticalLayoutWidget);
        tableVertLayout->setObjectName(QString::fromUtf8("tableVertLayout"));
        tableVertLayout->setContentsMargins(0, 0, 0, 0);
        SectionsTable = new QTableWidget(verticalLayoutWidget);
        SectionsTable->setObjectName(QString::fromUtf8("SectionsTable"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        SectionsTable->setFont(font1);
        SectionsTable->horizontalHeader()->setCascadingSectionResizes(false);
        SectionsTable->verticalHeader()->setCascadingSectionResizes(false);

        tableVertLayout->addWidget(SectionsTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(25, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        tableVertLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        tableVertLayout->addItem(verticalSpacer);


        retranslateUi(SectionsViewClass);
        QObject::connect(pushButton, SIGNAL(clicked()), SectionsViewClass, SLOT(closeView()));

        QMetaObject::connectSlotsByName(SectionsViewClass);
    } // setupUi

    void retranslateUi(QWidget *SectionsViewClass)
    {
        SectionsViewClass->setWindowTitle(QCoreApplication::translate("SectionsViewClass", "PE Sections", nullptr));
        pushButton->setText(QCoreApplication::translate("SectionsViewClass", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SectionsViewClass: public Ui_SectionsViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECTIONSVIEW_H
