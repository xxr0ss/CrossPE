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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CrossPEClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLineEdit *lineEditFileName;
    QLabel *label;
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
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(true);
        pushButton->setGeometry(QRect(30, 80, 93, 28));
        lineEditFileName = new QLineEdit(centralWidget);
        lineEditFileName->setObjectName(QString::fromUtf8("lineEditFileName"));
        lineEditFileName->setGeometry(QRect(100, 30, 381, 21));
        lineEditFileName->setReadOnly(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 72, 15));
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
        QObject::connect(actionOpen, SIGNAL(triggered()), CrossPEClass, SLOT(fileOpenFromMemuBar()));

        QMetaObject::connectSlotsByName(CrossPEClass);
    } // setupUi

    void retranslateUi(QMainWindow *CrossPEClass)
    {
        CrossPEClass->setWindowTitle(QCoreApplication::translate("CrossPEClass", "CrossPE", nullptr));
        actionOpen->setText(QCoreApplication::translate("CrossPEClass", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("CrossPEClass", "Save", nullptr));
        actionSave_As->setText(QCoreApplication::translate("CrossPEClass", "Save As", nullptr));
        pushButton->setText(QCoreApplication::translate("CrossPEClass", "Sections", nullptr));
        label->setText(QCoreApplication::translate("CrossPEClass", "PE file", nullptr));
        menuFile->setTitle(QCoreApplication::translate("CrossPEClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CrossPEClass: public Ui_CrossPEClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CROSSPE_H
