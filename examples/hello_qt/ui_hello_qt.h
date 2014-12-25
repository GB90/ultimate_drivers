/********************************************************************************
** Form generated from reading UI file 'hello_qt.ui'
**
** Created: Thu Dec 25 16:39:39 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLO_QT_H
#define UI_HELLO_QT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hello_qtClass
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QTableView *tableView;
    QRadioButton *radioButton;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QProgressBar *progressBar;

    void setupUi(QWidget *hello_qtClass)
    {
        if (hello_qtClass->objectName().isEmpty())
            hello_qtClass->setObjectName(QString::fromUtf8("hello_qtClass"));
        hello_qtClass->resize(160, 160);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hello_qtClass->sizePolicy().hasHeightForWidth());
        hello_qtClass->setSizePolicy(sizePolicy);

        QFont font;
        font.setFamily(("wenquanyi"));
        font.setPointSize(12);

        hello_qtClass->setFont(font);
        hello_qtClass->setWindowTitle(QString::fromUtf8("hello_qt"));
        hello_qtClass->setWindowFlags(Qt::FramelessWindowHint);
        label = new QLabel(hello_qtClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 61, 20));
        lineEdit = new QLineEdit(hello_qtClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(70, 10, 71, 21));
        tableView = new QTableView(hello_qtClass);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 90, 141, 61));
        radioButton = new QRadioButton(hello_qtClass);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 30, 71, 25));
        checkBox = new QCheckBox(hello_qtClass);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(80, 30, 61, 25));
        pushButton = new QPushButton(hello_qtClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 58, 51, 26));
        progressBar = new QProgressBar(hello_qtClass);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(70, 60, 81, 23));
        progressBar->setValue(24);

        retranslateUi(hello_qtClass);

        QMetaObject::connectSlotsByName(hello_qtClass);
    } // setupUi

    void retranslateUi(QWidget *hello_qtClass)
    {
        label->setText(QApplication::translate("hello_qtClass", "\346\214\211\351\224\256\345\200\274", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("hello_qtClass", "0", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("hello_qtClass", "\345\215\225\351\200\211", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("hello_qtClass", "\345\244\232\351\200\211", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("hello_qtClass", "\346\214\211\351\222\256", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(hello_qtClass);
    } // retranslateUi

};

namespace Ui {
    class hello_qtClass: public Ui_hello_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLO_QT_H
