/********************************************************************************
** Form generated from reading UI file 'dialog_log.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_LOG_H
#define UI_DIALOG_LOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog_log
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog_log)
    {
        if (Dialog_log->objectName().isEmpty())
            Dialog_log->setObjectName("Dialog_log");
        Dialog_log->resize(234, 72);
        formLayout = new QFormLayout(Dialog_log);
        formLayout->setObjectName("formLayout");
        label = new QLabel(Dialog_log);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(Dialog_log);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        buttonBox = new QDialogButtonBox(Dialog_log);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(1, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(Dialog_log);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog_log, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog_log, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog_log);
    } // setupUi

    void retranslateUi(QDialog *Dialog_log)
    {
        Dialog_log->setWindowTitle(QCoreApplication::translate("Dialog_log", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog_log", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_log: public Ui_Dialog_log {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_LOG_H
