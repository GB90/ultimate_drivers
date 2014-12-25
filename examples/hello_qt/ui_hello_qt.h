/********************************************************************************
** Form generated from reading UI file 'hello_qt.ui'
**
** Created: Thu Dec 25 16:18:34 2014
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
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hello_qtClass
{
public:
    QRadioButton *radioButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QCheckBox *checkBox;
    QListWidget *listWidget;

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
        hello_qtClass->setMinimumSize(QSize(160, 160));
        hello_qtClass->setMaximumSize(QSize(160, 160));
        hello_qtClass->setBaseSize(QSize(160, 160));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\347\202\271\351\230\265\346\255\243\351\273\221"));
        font.setPointSize(12);
        hello_qtClass->setFont(font);
        hello_qtClass->setCursor(QCursor(Qt::BlankCursor));
        radioButton = new QRadioButton(hello_qtClass);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 95, 71, 20));
        lineEdit = new QLineEdit(hello_qtClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 10, 61, 21));
        label = new QLabel(hello_qtClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 66, 20));
        pushButton = new QPushButton(hello_qtClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 119, 61, 31));
        progressBar = new QProgressBar(hello_qtClass);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(80, 121, 71, 28));
        progressBar->setValue(24);
        checkBox = new QCheckBox(hello_qtClass);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(80, 95, 71, 20));
        listWidget = new QListWidget(hello_qtClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 40, 141, 51));

        retranslateUi(hello_qtClass);

        QMetaObject::connectSlotsByName(hello_qtClass);
    } // setupUi

    void retranslateUi(QWidget *hello_qtClass)
    {
        hello_qtClass->setWindowTitle(QApplication::translate("hello_qtClass", "hello", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("hello_qtClass", "\351\200\211\344\270\255", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("hello_qtClass", "100", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("hello_qtClass", "\346\214\211\351\224\256\345\200\274", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("hello_qtClass", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("hello_qtClass", "\346\211\223\345\213\276", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class hello_qtClass: public Ui_hello_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLO_QT_H
