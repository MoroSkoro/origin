/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QDialogButtonBox *buttonBox;
    QGroupBox *gB_connection;
    QFormLayout *formLayout_2;
    QLabel *lab_host;
    QLineEdit *lineE_host;
    QLabel *lab_nameBD;
    QLineEdit *lineE_nameBD;
    QLabel *lab_port;
    QSpinBox *spB_port;
    QLabel *lab_log;
    QLineEdit *lineE_log;
    QLabel *lab_parole;
    QLineEdit *lineE_parole;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(436, 420);
        MainWindow->setMinimumSize(QSize(288, 406));
        MainWindow->setMaximumSize(QSize(488, 420));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(288, 363));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName("buttonBox");
        QFont font;
        font.setPointSize(10);
        buttonBox->setFont(font);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        gridLayout_2->addWidget(buttonBox, 2, 0, 1, 1);

        gB_connection = new QGroupBox(centralwidget);
        gB_connection->setObjectName("gB_connection");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        gB_connection->setFont(font1);
        gB_connection->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        gB_connection->setFlat(false);
        formLayout_2 = new QFormLayout(gB_connection);
        formLayout_2->setObjectName("formLayout_2");
        lab_host = new QLabel(gB_connection);
        lab_host->setObjectName("lab_host");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, lab_host);

        lineE_host = new QLineEdit(gB_connection);
        lineE_host->setObjectName("lineE_host");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineE_host);

        lab_nameBD = new QLabel(gB_connection);
        lab_nameBD->setObjectName("lab_nameBD");

        formLayout_2->setWidget(2, QFormLayout::LabelRole, lab_nameBD);

        lineE_nameBD = new QLineEdit(gB_connection);
        lineE_nameBD->setObjectName("lineE_nameBD");

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lineE_nameBD);

        lab_port = new QLabel(gB_connection);
        lab_port->setObjectName("lab_port");

        formLayout_2->setWidget(4, QFormLayout::SpanningRole, lab_port);

        spB_port = new QSpinBox(gB_connection);
        spB_port->setObjectName("spB_port");
        spB_port->setWrapping(false);
        spB_port->setFrame(true);
        spB_port->setReadOnly(false);
        spB_port->setButtonSymbols(QAbstractSpinBox::UpDownArrows);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, spB_port);

        lab_log = new QLabel(gB_connection);
        lab_log->setObjectName("lab_log");

        formLayout_2->setWidget(6, QFormLayout::LabelRole, lab_log);

        lineE_log = new QLineEdit(gB_connection);
        lineE_log->setObjectName("lineE_log");

        formLayout_2->setWidget(6, QFormLayout::FieldRole, lineE_log);

        lab_parole = new QLabel(gB_connection);
        lab_parole->setObjectName("lab_parole");

        formLayout_2->setWidget(8, QFormLayout::LabelRole, lab_parole);

        lineE_parole = new QLineEdit(gB_connection);
        lineE_parole->setObjectName("lineE_parole");

        formLayout_2->setWidget(8, QFormLayout::FieldRole, lineE_parole);


        gridLayout_2->addWidget(gB_connection, 0, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        gridLayout_2->addWidget(pushButton, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 436, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
#if QT_CONFIG(shortcut)
        lab_host->setBuddy(lineE_host);
        lab_nameBD->setBuddy(lineE_nameBD);
        lab_port->setBuddy(spB_port);
        lab_log->setBuddy(lineE_log);
        lab_parole->setBuddy(lineE_parole);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(lineE_host, lineE_nameBD);
        QWidget::setTabOrder(lineE_nameBD, spB_port);
        QWidget::setTabOrder(spB_port, lineE_log);
        QWidget::setTabOrder(lineE_log, lineE_parole);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BD", nullptr));
        gB_connection->setTitle(QString());
        lab_host->setText(QCoreApplication::translate("MainWindow", "&\320\230\320\274\321\217 \321\205\320\276\321\201\321\202\320\260", nullptr));
        lab_nameBD->setText(QCoreApplication::translate("MainWindow", "&\320\230\320\274\321\217 \320\221\320\224", nullptr));
        lab_port->setText(QCoreApplication::translate("MainWindow", "&\320\237\320\276\321\200\321\202 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\321\217 \320\221\320\224", nullptr));
        lab_log->setText(QCoreApplication::translate("MainWindow", "&\320\233\320\276\320\263\320\270\320\275", nullptr));
        lab_parole->setText(QCoreApplication::translate("MainWindow", "&\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
