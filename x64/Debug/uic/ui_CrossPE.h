/********************************************************************************
** Form generated from reading UI file 'CrossPE.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CROSSPE_H
#define UI_CROSSPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CrossPEClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QWidget *centralWidget;
    QPushButton *btnOpenSectionView;
    QLineEdit *lineEditFileName;
    QLabel *label;
    QToolButton *toolButton;
    QPushButton *btnOpenImportTable;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QTextEdit *basicPEinfo;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CrossPEClass)
    {
        if (CrossPEClass->objectName().isEmpty())
            CrossPEClass->setObjectName(QString::fromUtf8("CrossPEClass"));
        CrossPEClass->resize(586, 347);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        CrossPEClass->setFont(font);
        actionOpen = new QAction(CrossPEClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(CrossPEClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_As = new QAction(CrossPEClass);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        centralWidget = new QWidget(CrossPEClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btnOpenSectionView = new QPushButton(centralWidget);
        btnOpenSectionView->setObjectName(QString::fromUtf8("btnOpenSectionView"));
        btnOpenSectionView->setEnabled(false);
        btnOpenSectionView->setGeometry(QRect(20, 190, 93, 28));
        lineEditFileName = new QLineEdit(centralWidget);
        lineEditFileName->setObjectName(QString::fromUtf8("lineEditFileName"));
        lineEditFileName->setGeometry(QRect(120, 10, 401, 21));
        lineEditFileName->setReadOnly(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 72, 15));
        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(530, 10, 47, 21));
        btnOpenImportTable = new QPushButton(centralWidget);
        btnOpenImportTable->setObjectName(QString::fromUtf8("btnOpenImportTable"));
        btnOpenImportTable->setEnabled(false);
        btnOpenImportTable->setGeometry(QRect(20, 150, 93, 28));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(false);
        pushButton_2->setGeometry(QRect(120, 150, 93, 28));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 40, 72, 15));
        basicPEinfo = new QTextEdit(centralWidget);
        basicPEinfo->setObjectName(QString::fromUtf8("basicPEinfo"));
        basicPEinfo->setEnabled(false);
        basicPEinfo->setGeometry(QRect(120, 40, 401, 91));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(9);
        basicPEinfo->setFont(font1);
        basicPEinfo->setReadOnly(true);
        basicPEinfo->setAcceptRichText(true);
        CrossPEClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CrossPEClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 586, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        CrossPEClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CrossPEClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CrossPEClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CrossPEClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CrossPEClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);

        retranslateUi(CrossPEClass);
        QObject::connect(actionOpen, SIGNAL(triggered()), CrossPEClass, SLOT(fileOpenWithDialog()));
        QObject::connect(toolButton, SIGNAL(clicked()), CrossPEClass, SLOT(fileOpenWithDialog()));

        QMetaObject::connectSlotsByName(CrossPEClass);
    } // setupUi

    void retranslateUi(QMainWindow *CrossPEClass)
    {
        CrossPEClass->setWindowTitle(QCoreApplication::translate("CrossPEClass", "CrossPE", nullptr));
        actionOpen->setText(QCoreApplication::translate("CrossPEClass", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("CrossPEClass", "Save", nullptr));
        actionSave_As->setText(QCoreApplication::translate("CrossPEClass", "Save As", nullptr));
        btnOpenSectionView->setText(QCoreApplication::translate("CrossPEClass", "Sections", nullptr));
        label->setText(QCoreApplication::translate("CrossPEClass", "PE file:", nullptr));
        toolButton->setText(QCoreApplication::translate("CrossPEClass", "...", nullptr));
        btnOpenImportTable->setText(QCoreApplication::translate("CrossPEClass", "Import", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CrossPEClass", "Export", nullptr));
        label_2->setText(QCoreApplication::translate("CrossPEClass", "Basic Info:", nullptr));
        menuFile->setTitle(QCoreApplication::translate("CrossPEClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CrossPEClass: public Ui_CrossPEClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CROSSPE_H
