/********************************************************************************
** Form generated from reading UI file 'qt_ui.ui'
**
** Created: Fri Dec 26 11:08:45 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_UI_H
#define UI_QT_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hello_qtClass
{
public:
    QPushButton *pushButton[9];
    QLineEdit *lineEdit;

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
        pushButton[0] = new QPushButton(hello_qtClass);
        pushButton[0]->setObjectName(QString::fromUtf8("pushButton[0]"));
        pushButton[0]->setGeometry(QRect(10, 60, 41, 30));
        pushButton[0]->setFocusPolicy(Qt::NoFocus);
        pushButton[3] = new QPushButton(hello_qtClass);
        pushButton[3]->setObjectName(QString::fromUtf8("pushButton[3]"));
        pushButton[3]->setGeometry(QRect(10, 90, 41, 30));
        pushButton[3]->setFocusPolicy(Qt::NoFocus);
        pushButton[4] = new QPushButton(hello_qtClass);
        pushButton[4]->setObjectName(QString::fromUtf8("pushButton[4]"));
        pushButton[4]->setGeometry(QRect(10, 120, 41, 30));
        pushButton[4]->setFocusPolicy(Qt::NoFocus);
        pushButton[6] = new QPushButton(hello_qtClass);
        pushButton[6]->setObjectName(QString::fromUtf8("pushButton[6]"));
        pushButton[6]->setGeometry(QRect(110, 60, 41, 30));
        pushButton[6]->setFocusPolicy(Qt::NoFocus);
        pushButton[7] = new QPushButton(hello_qtClass);
        pushButton[7]->setObjectName(QString::fromUtf8("pushButton[7]"));
        pushButton[7]->setGeometry(QRect(110, 90, 41, 30));
        pushButton[7]->setFocusPolicy(Qt::NoFocus);
        pushButton[8] = new QPushButton(hello_qtClass);
        pushButton[8]->setObjectName(QString::fromUtf8("pushButton[8]"));
        pushButton[8]->setGeometry(QRect(110, 120, 41, 30));
        pushButton[8]->setFocusPolicy(Qt::NoFocus);
        pushButton[1] = new QPushButton(hello_qtClass);
        pushButton[1]->setObjectName(QString::fromUtf8("pushButton[1]"));
        pushButton[1]->setGeometry(QRect(60, 60, 41, 30));
        pushButton[1]->setFocusPolicy(Qt::NoFocus);
        pushButton[2] = new QPushButton(hello_qtClass);
        pushButton[2]->setObjectName(QString::fromUtf8("pushButton[2]"));
        pushButton[2]->setGeometry(QRect(60, 90, 41, 30));
        pushButton[2]->setFocusPolicy(Qt::NoFocus);
        pushButton[5] = new QPushButton(hello_qtClass);
        pushButton[5]->setObjectName(QString::fromUtf8("pushButton[5]"));
        pushButton[5]->setGeometry(QRect(60, 120, 41, 30));
        pushButton[5]->setFocusPolicy(Qt::NoFocus);
        lineEdit = new QLineEdit(hello_qtClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 141, 41));

        retranslateUi(hello_qtClass);

        QMetaObject::connectSlotsByName(hello_qtClass);
    } // setupUi

    void retranslateUi(QWidget *hello_qtClass)
    {
        pushButton[0]->setText(QApplication::translate("hello_qtClass", "1", 0, QApplication::UnicodeUTF8));
        pushButton[3]->setText(QApplication::translate("hello_qtClass", "4", 0, QApplication::UnicodeUTF8));
        pushButton[4]->setText(QApplication::translate("hello_qtClass", "7", 0, QApplication::UnicodeUTF8));
        pushButton[6]->setText(QApplication::translate("hello_qtClass", "3", 0, QApplication::UnicodeUTF8));
        pushButton[7]->setText(QApplication::translate("hello_qtClass", "6", 0, QApplication::UnicodeUTF8));
        pushButton[8]->setText(QApplication::translate("hello_qtClass", "9", 0, QApplication::UnicodeUTF8));
        pushButton[1]->setText(QApplication::translate("hello_qtClass", "2", 0, QApplication::UnicodeUTF8));
        pushButton[2]->setText(QApplication::translate("hello_qtClass", "5", 0, QApplication::UnicodeUTF8));
        pushButton[5]->setText(QApplication::translate("hello_qtClass", "8", 0, QApplication::UnicodeUTF8));
        lineEdit->setInputMask(QString());
        lineEdit->setText(QApplication::translate("hello_qtClass", "0", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(hello_qtClass);
    } // retranslateUi

};

namespace Ui {
    class hello_qtClass: public Ui_hello_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_UI_H
