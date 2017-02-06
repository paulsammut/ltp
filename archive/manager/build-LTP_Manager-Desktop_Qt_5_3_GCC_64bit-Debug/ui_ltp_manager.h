/********************************************************************************
** Form generated from reading UI file 'ltp_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LTP_MANAGER_H
#define UI_LTP_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LTP_Manager
{
public:
    QWidget *centralWidget;
    QPushButton *button_Quit;
    QTextEdit *textBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *button_Connect;
    QPushButton *button_Disconnect;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LTP_Manager)
    {
        if (LTP_Manager->objectName().isEmpty())
            LTP_Manager->setObjectName(QStringLiteral("LTP_Manager"));
        LTP_Manager->resize(456, 326);
        centralWidget = new QWidget(LTP_Manager);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        button_Quit = new QPushButton(centralWidget);
        button_Quit->setObjectName(QStringLiteral("button_Quit"));
        button_Quit->setGeometry(QRect(40, 210, 96, 27));
        textBox = new QTextEdit(centralWidget);
        textBox->setObjectName(QStringLiteral("textBox"));
        textBox->setGeometry(QRect(190, 20, 211, 141));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 10, 95, 63));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        button_Connect = new QPushButton(widget);
        button_Connect->setObjectName(QStringLiteral("button_Connect"));

        verticalLayout->addWidget(button_Connect);

        button_Disconnect = new QPushButton(widget);
        button_Disconnect->setObjectName(QStringLiteral("button_Disconnect"));

        verticalLayout->addWidget(button_Disconnect);

        LTP_Manager->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LTP_Manager);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 456, 23));
        LTP_Manager->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LTP_Manager);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LTP_Manager->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LTP_Manager);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LTP_Manager->setStatusBar(statusBar);

        retranslateUi(LTP_Manager);

        QMetaObject::connectSlotsByName(LTP_Manager);
    } // setupUi

    void retranslateUi(QMainWindow *LTP_Manager)
    {
        LTP_Manager->setWindowTitle(QApplication::translate("LTP_Manager", "LTP_Manager", 0));
        button_Quit->setText(QApplication::translate("LTP_Manager", "Quit", 0));
        button_Connect->setText(QApplication::translate("LTP_Manager", "Connect", 0));
        button_Disconnect->setText(QApplication::translate("LTP_Manager", "Disconnect", 0));
    } // retranslateUi

};

namespace Ui {
    class LTP_Manager: public Ui_LTP_Manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LTP_MANAGER_H
