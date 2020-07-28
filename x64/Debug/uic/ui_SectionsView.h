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
#include <QtWidgets/QHeaderView>
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

    void setupUi(QWidget *SectionsViewClass)
    {
        if (SectionsViewClass->objectName().isEmpty())
            SectionsViewClass->setObjectName(QString::fromUtf8("SectionsViewClass"));
        SectionsViewClass->resize(643, 300);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        SectionsViewClass->setFont(font);
        verticalLayoutWidget = new QWidget(SectionsViewClass);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 621, 281));
        tableVertLayout = new QVBoxLayout(verticalLayoutWidget);
        tableVertLayout->setObjectName(QString::fromUtf8("tableVertLayout"));
        tableVertLayout->setContentsMargins(0, 0, 0, 0);
        SectionsTable = new QTableWidget(verticalLayoutWidget);
        SectionsTable->setObjectName(QString::fromUtf8("SectionsTable"));
        SectionsTable->horizontalHeader()->setCascadingSectionResizes(false);
        SectionsTable->verticalHeader()->setCascadingSectionResizes(false);

        tableVertLayout->addWidget(SectionsTable);


        retranslateUi(SectionsViewClass);

        QMetaObject::connectSlotsByName(SectionsViewClass);
    } // setupUi

    void retranslateUi(QWidget *SectionsViewClass)
    {
        SectionsViewClass->setWindowTitle(QCoreApplication::translate("SectionsViewClass", "PE Sections", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SectionsViewClass: public Ui_SectionsViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECTIONSVIEW_H
